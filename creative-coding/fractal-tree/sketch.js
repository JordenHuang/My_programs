let angle;
let theta;
let slider;

function setup() {
  createCanvas(800, 800);
  colorMode(HSL);

  slider = createSlider(0, 10, 5);
  slider.position(10, 10);
  slider.size(80);
}

function draw() {
  background(0);

  let depth = slider.value();

  angle = 10 + mouseX/width * 360;
  theta = Math.PI / 180 * angle;

  let trunk = new Branch(
    // new Vector2(width/2, height*0.95),
    // new Vector2(width/2, height*0.65),
    new Vector2(width/2, height*0.5),
    new Vector2(width/2, height*0.35),
    0,
    color(10, 45, 40)
  );
  trunk.draw();
  growBranches(trunk, depth);

  let trunk2 = new Branch(
    new Vector2(width/2, height*0.5),
    new Vector2(width/2, height*0.65),
    0,
    color(10, 45, 40)
  );
  trunk2.draw();
  growBranches(trunk2, depth);

  let trunk3 = new Branch(
    new Vector2(height*0.5, width/2),
    new Vector2(height*0.35, width/2),
    0,
    color(10, 45, 40)
  );
  trunk3.draw();
  growBranches(trunk3, depth);

  let trunk4 = new Branch(
    new Vector2(height*0.5, width/2),
    new Vector2(height*0.65, width/2),
    0,
    color(10, 45, 40)
  );
  trunk4.draw();
  growBranches(trunk4, depth);
}

function growBranches(root, depth) {
  let currentDepth = 0;
  let branchColor = 255;

  let i = 0;
  let branches = [];
  branches.push(root);

  let b, lastTip, d, lx, ly, lTip, l, rx, ry, rTip, r;
  let newDepth, newColor;
  // BFS
  while (i != branches.length) {
    b = branches[i];
    newDepth = b.depth + 1;
    newColor = color(110, 75, (1-(newDepth/depth)*0.8)*100);
    d = Vector2.direction(b.root, b.tip);
    d.mul(1/Math.sqrt(2));

    // left branch
    lTip = Vector2.rotate(d, theta);
    lx = b.tip.x + lTip.x;
    ly = b.tip.y + lTip.y;
    l = new Branch(b.tip, new Vector2(lx, ly), newDepth, newColor);

    // right branch
    rTip = Vector2.rotate(d, -theta);
    rx = b.tip.x + rTip.x;
    ry = b.tip.y + rTip.y;
    r = new Branch(b.tip, new Vector2(rx, ry), newDepth, newColor);

    l.draw();
    r.draw();

    if (newDepth < depth) {
      branches.push(l, r);
    }

    i++;
  }
}

class Vector2 {
  static direction(from, to) {
    return new Vector2(to.x - from.x, to.y - from.y);
  }

  static rotate(v, theta) {
    let newX = v.x * Math.cos(theta) - v.y * Math.sin(theta);
    let newY = v.x * Math.sin(theta) + v.y * Math.cos(theta);
    return new Vector2(newX, newY);
  }

  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  length() {
    return Math.sqrt(this.x*this.x + this.y*this.y);
  }

  add(v) {
    this.x += v.x;
    this.y += v.y;
  }

  mul(m) {
    this.x *= m;
    this.y *= m;
  }
}

class Branch {
  constructor(root, tip, depth, color) {
    this.root = root;
    this.tip = tip;
    this.depth = depth;
    this.color = color;
  }

  draw() {
    stroke(this.color);
    strokeWeight(2);
    line(this.root.x, this.root.y, this.tip.x, this.tip.y);
  }
}
