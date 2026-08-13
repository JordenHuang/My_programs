// let CANVAS_SIZE = 512;
let CANVAS_SIZE = 640;
let rows = 2;
let cellSize = CANVAS_SIZE / rows;

const Directions = Object.freeze({
  UP: 0,
  RIGHT: 1,
  DOWN: 2,
  LEFT: 3,
  _DIRECTION_COUNT: 4,
});

const LSystem = Object.freeze({
  A: "+BF-AFA-FB+",
  B: "-AF+BFB+FA-",
});

const MAX_DEPTH = 9;
let n = 1;
let curX;
let curY;
let nextX;
let nextY;
let direction;
let path = [];
let pathIdx = 0;

function setup() {
  createCanvas(CANVAS_SIZE, CANVAS_SIZE);
  colorMode(HSL);
}

function draw() {
  background(0);
  // drawGrid();

  if (pathIdx == 0) {
    curX = cellSize / 2;
    curY = height - cellSize / 2;
    direction = Directions.UP;
    hilbertCurve(n);
    pathIdx++;
  } else if (pathIdx == path.length) {
    n += 1;
    rows *= 2;
    cellSize = CANVAS_SIZE / rows;
    pathIdx = 0;
    path = [];
  } else {
    strokeWeight(2);
    for (let i = 1; i <= pathIdx; i++) {
      let baseColor = color((i/pathIdx * 360 + pathIdx) % 360, 75, 50);
      stroke(baseColor);
      line(path[i - 1].x, path[i - 1].y, path[i].x, path[i].y);
    }
    pathIdx += 1;
  }

  if (n >= MAX_DEPTH) {
    n = 1;
    rows = 2;
    cellSize = CANVAS_SIZE / rows;
    pathIdx = 0;
    path = [];
  }
}

function drawGrid() {
  noFill();
  stroke(159);
  rect(0, 0, CANVAS_SIZE, CANVAS_SIZE);
  for (let i = 0; i < rows; i++) {
    line(0, i*cellSize, CANVAS_SIZE, i*cellSize);
    line(i*cellSize, 0, i*cellSize, CANVAS_SIZE);
  }
}

function hilbertCurve(n) {
  path.push({x: curX, y: curY});
  hilbertConstruct(n, LSystem.A);
}

function hilbertConstruct(depth, type) {
  if (depth === 0) return;

  let s = LSystem.A;

  if (type == LSystem.B)
    s = LSystem.B;

  for (let i = 0; i < s.length; i++) {
    switch (s[i]) {
      case '+':
        direction = (direction + 1) % Directions._DIRECTION_COUNT;
        break;
      case '-':
        direction = (direction + Directions._DIRECTION_COUNT - 1) % Directions._DIRECTION_COUNT;
        break;
      case 'F':
        switch (direction) {
          case Directions.UP:
            nextX = curX;
            nextY = curY - cellSize;
            break;
          case Directions.RIGHT:
            nextX = curX + cellSize;
            nextY = curY;
            break;
          case Directions.DOWN:
            nextX = curX;
            nextY = curY + cellSize;
            break;
          case Directions.LEFT:
            nextX = curX - cellSize;
            nextY = curY;
            break;
          default:
            break;
        }
        path.push({x: nextX, y: nextY});

        curX = nextX;
        curY = nextY;
        break;
      case 'A':
        if (depth > 1)
          hilbertConstruct(depth - 1, LSystem.A);
        break;
      case 'B':
        if (depth > 1)
          hilbertConstruct(depth - 1, LSystem.B);
        break;
      default:
        break;
    }
  }
}
