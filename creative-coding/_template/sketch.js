function setup() {
  createCanvas(600, 400);
}

function draw() {
  background(135, 206, 235);

  // Sun
  fill("yellow");
  stroke("orange");
  strokeWeight(20);
  circle(550, 50, 100);

  // Grass
  stroke(0);
  strokeWeight(1);
  fill("green");
  rect(0, 200, 600, 200);

  // Emojis
  textSize(75);
  text("🌸", 100, 250);
  text("🐞", mouseX, mouseY);
}
