// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ 
// https://github.com/Jade570/p5js-fps_example/tree/master
// https://cdn.jsdelivr.net/npm/p5-first-person-camera@1.0.1/FirstPersonCamera.js

let pointerIsLocked = false;

let position;
// horizontal angle : toward -Z
let horizontalAngle;
// vertical angle : 0, look at the horizon
let verticalAngle;
// Initial Field of View
let initialFoV;

let speed = 0.5; // 3 units / second
let mouseSpeed = 0.0003;

let direction;
let right;
let up;
let camLookat;

let keyForward, keyBack, keyLeft, keyRight;

let boxSize = 50;
let worldSize = 10;
let voxelGrid = [];
let chunkGeometry;

function setup() {
  createCanvas(600, 400, WEBGL);

  position = createVector(0, 0, 0);
  horizontalAngle = 3.14;
  verticalAngle = 0.0;
  initialFoV = 45.0;
  up = createVector(0, 1, 0);
  right = createVector(1, 0, 0);
  camLookat = createVector(0, 0, 0);

  document.addEventListener('pointerlockchange', onLockChange, false);

  // setupGrid();
  // chunkGeometry = buildGeometry(generateChunk);
}

function draw() {
  background(135, 206, 235);

  handlePlayer();

  renderScene();
  // model(chunkGeometry);

  // drawFrontFace(boxSize);

  updateUI();
}

function handlePlayer() {
  if (pointerIsLocked === true) {
    horizontalAngle += mouseSpeed * deltaTime * movedX * -1;
    verticalAngle += mouseSpeed * deltaTime * movedY;
    verticalAngle = constrain(verticalAngle, -1.57, 1.57);

    let walkDirection = createVector(
      Math.sin(horizontalAngle),
      0,
      Math.cos(horizontalAngle)
    );

    let rightDirection = createVector(
      Math.sin(horizontalAngle - Math.PI/2),
      0,
      Math.cos(horizontalAngle - Math.PI/2)
    );

    let walkStep = p5.Vector.mult(walkDirection, deltaTime * speed);
    let sideStep = p5.Vector.mult(rightDirection, deltaTime * speed);
    console.log(walkStep.z, position.z);

    // Movement controls
    // let dds = p5.Vector.mult(direction, deltaTime * speed);
    // let rds = p5.Vector.mult(right, deltaTime * speed);
    let uds = p5.Vector.mult(up, deltaTime * speed);
    // w
    if (keyIsDown(87) || keyIsDown(UP_ARROW)) {
      position.add(walkStep);
    }
    // s
    if (keyIsDown(83) || keyIsDown(DOWN_ARROW)) {
      position.sub(walkStep);
    }
    // a
    if (keyIsDown(65) || keyIsDown(LEFT_ARROW)) {
      position.sub(sideStep);
    }
    // d
    if (keyIsDown(68) || keyIsDown(RIGHT_ARROW)) {
      position.add(sideStep);
    }
    // SPACE
    if (keyIsDown(32)) {
      // p5.js's Y axis is pointed down, so fly up needs to decrease y value
      position.sub(uds);
    }
    // SHIFT
    if (keyIsDown(SHIFT)) {
      // p5.js's Y axis is pointed down, so fly down needs to increase y value
      position.add(uds);
    }
  }

  direction = createVector(
    Math.cos(verticalAngle) * Math.sin(horizontalAngle),
    Math.sin(verticalAngle),
    Math.cos(verticalAngle) * Math.cos(horizontalAngle)
  );

  right = createVector(
    Math.sin(horizontalAngle - 3.14/2.0),
    0,
    Math.cos(horizontalAngle - 3.14/2.0)
  );

  // up = right.cross(direction);

  camLookat = p5.Vector.add(position, direction);

  camera(
    position.x, position.y, position.z,
    camLookat.x, camLookat.y, camLookat.z,
    up.x, up.y, up.z
  );
}

function renderScene() {
  let boxCount = 3;

  push();
  // x
  for (let i = 0; i < boxCount; i++) {
    push();
    translate(boxSize * i, 0, -400);
    // y
    for (let j = 0; j < boxCount; j++) {
      push();
      box(boxSize);
      translate(0, -boxSize * j, 0);
      // z
      for (let k = 0; k < boxCount; k++) {
        box(boxSize);
        translate(0, 0, -boxSize);
      }
      pop();
    }
    pop();
  }
  pop();
}

function updateUI() {
  // cursor
  let cursorSize = 8;
  drawingContext.clear(drawingContext.DEPTH_BUFFER_BIT);
  camera();
  push();
  strokeWeight(2);
  line(-cursorSize, 0, cursorSize, 0);
  line(0, -cursorSize, 0, cursorSize);
  pop();
}

function mouseClicked() {
  //lock pointer
  requestPointerLock();
  pointerIsLocked = true;
}

function onLockChange() {
  if (document.pointerLockElement !== canvas) {
    exitPointerLock();
    pointerIsLocked = false;
  }
}

function setupGrid() {
  for (let x = 0; x < worldSize; x++) {
    voxelGrid[x] = [];
    for (let y = 0; y < worldSize; y++) {
      voxelGrid[x][y] = [];
      for (let z = 0; z < worldSize; z++) {
        voxelGrid[x][y][z] = 1; // 假設全部都是實心方塊
      }
    }
  }
}

function getVoxel(x, y, z) {
  if (x < 0 || x >= worldSize || y < 0 || y >= worldSize || z < 0 || z >= worldSize) {
    return 0; // 超出邊界視為空氣
  }
  return voxelGrid[x][y][z];
}

function generateChunk() {
  push();
  translate(0, 0, boxSize * (worldSize * -3/2));
  for (let x = 0; x < worldSize; x++) {
    for (let y = 0; y < worldSize; y++) {
      for (let z = 0; z < worldSize; z++) {
        
        // 如果這裡是空氣，跳過
        if (getVoxel(x, y, z) === 0) continue;
        
        let px = x * boxSize;
        let py = y * boxSize;
        let pz = z * boxSize;
        
        // 準備畫這個方塊的面
        // 注意：這裡我們把原點移到該方塊的中心，畫完面再移回來
        push();
        translate(px, py, pz);
        
        // 檢查右邊 (X+1)
        if (getVoxel(x + 1, y, z) === 0) drawFace("RIGHT", boxSize);
        // 檢查左邊 (X-1)
        if (getVoxel(x - 1, y, z) === 0) drawFace("LEFT", boxSize);
        // 檢查上面 (Y-1) - 注意 Y 軸方向
        if (getVoxel(x, y - 1, z) === 0) drawFace("TOP", boxSize);
        // 檢查下面 (Y+1)
        if (getVoxel(x, y + 1, z) === 0) drawFace("BOTTOM", boxSize);
        // 檢查前面 (Z+1)
        if (getVoxel(x, y, z + 1) === 0) drawFace("FRONT", boxSize);
        // 檢查後面 (Z-1)
        if (getVoxel(x, y, z - 1) === 0) drawFace("BACK", boxSize);
        
        pop();
      }
    }
  }
  pop();
}

// 根據方向繪製單一個四邊形
function drawFace(dir, s) {
  let r = s / 2;
  beginShape(QUADS);
  if (dir === "FRONT") {
    vertex(-r, -r, r); vertex( r, -r, r); vertex( r,  r, r); vertex(-r,  r, r);
  } else if (dir === "BACK") {
    vertex(-r, -r, -r); vertex( r, -r, -r); vertex( r,  r, -r); vertex(-r,  r, -r);
  } else if (dir === "TOP") {
    vertex(-r, -r, -r); vertex( r, -r, -r); vertex( r, -r,  r); vertex(-r, -r,  r);
  } else if (dir === "BOTTOM") {
    vertex(-r,  r, -r); vertex( r,  r, -r); vertex( r,  r,  r); vertex(-r,  r,  r);
  } else if (dir === "RIGHT") {
    vertex( r, -r, -r); vertex( r, -r,  r); vertex( r,  r,  r); vertex( r,  r, -r);
  } else if (dir === "LEFT") {
    vertex(-r, -r, -r); vertex(-r, -r,  r); vertex(-r,  r,  r); vertex(-r,  r, -r);
  }
  endShape();
}

// 畫一個由純三角形組成的面
function drawFrontFace(boxSize) {
  let r = boxSize / 2; // 半徑
  
  // 定義正面的 4 個角落 (假設 Z 軸朝向我們，Z = r)
  // 注意這裡的座標系統：X 往右為正，Y 往下為正
  let topLeft     = createVector(-r, -r, r);
  let bottomLeft  = createVector(-r,  r, r);
  let bottomRight = createVector( r,  r, r);
  let topRight    = createVector( r, -r, r);

  beginShape(TRIANGLES);
  
  // ==========================================
  // 第一個三角形：左半部 (TopLeft -> BottomLeft -> BottomRight)
  // 在畫面上這三個點會形成「逆時針」方向！
  // ==========================================
  // 頂點 1
  vertex(topLeft.x, topLeft.y, topLeft.z); 
  // 頂點 2
  vertex(bottomLeft.x, bottomLeft.y, bottomLeft.z); 
  // 頂點 3
  vertex(bottomRight.x, bottomRight.y, bottomRight.z); 

  // ==========================================
  // 第二個三角形：右半部 (TopLeft -> BottomRight -> TopRight)
  // 在畫面上這三個點也會形成「逆時針」方向！
  // ==========================================
  // 頂點 4
  vertex(topLeft.x, topLeft.y, topLeft.z); 
  // 頂點 5
  vertex(bottomRight.x, bottomRight.y, bottomRight.z); 
  // 頂點 6
  vertex(topRight.x, topRight.y, topRight.z); 
  
  endShape();
}
