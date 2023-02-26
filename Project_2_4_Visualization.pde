import processing.serial.*;

Serial myPort;
String val; //string to store port

//graph cordinates
int graphStart = 100;
int graphEnd = 600;
int graphTop = 100;
int graphBottom = 300;

//data varaibles
int[] temps = new int[14400];
int sampleNum = 0;

//graphing varaibles
int lowIndex, highIndex;

boolean update = false;

void setup() {
  //setup serial
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);

  size(900, 400);
}

void draw() {
  if (update) {
    setupBackground();            //clear and redraw
    graph(lowIndex, highIndex);   //new graph
  }
}

void setupBackground() {
  background(255, 255, 255);  //clear
  //draw graph
  line(graphStart, graphTop, graphStart, graphBottom);
  line(graphStart, graphBottom, graphEnd, graphBottom);
  //draw buttons
  rectMode(CORNERS);
  rect(700, 100, 800, 300);
  line(750, 100, 750, 300);
  fill(0);
  text("Hour Number", 700, 100);    //label
  noFill();
  for (int row = 0; row <= 11; row++) {    //draw the row dividors
    line(700, row * 16.6 + 100, 800, row * 16.6 + 100);
    fill(0);
    text(row, 700, row * 16.6 + 116.6);        //left draw label
    text(row + 12, 750, row * 16.6 + 116.6);   //right row label
    noFill();
  }
  rect(725, 325, 775, 350);  //24 hour button
  fill(0);
  text("Whole Day", 725, 337.5);  //24 hour button label
  text("Time", (graphEnd + graphStart)/2, graphBottom + 15);      //x name
  text("Temp(ºC)", graphStart - 50, (graphBottom + graphTop)/2);  //y name
  text("50", graphStart - 15, graphTop + 5);                      //y top
  text("0", graphStart - 15, graphBottom + 5);                    //y bottom
  noFill();
}

void mouseClicked() {
  update = true;
  
  /* Same for all
  * Check position
  * Then set bottom and top index for that button's hour
  */
  if (in0()) {
    lowIndex = 0;
    highIndex = 600;
  } else if (in1()) {
    lowIndex = 600;
    highIndex = 2 * 600;
  } else if (in2()) {
    lowIndex = 2 * 600;
    highIndex = 3 * 600;
  } else if (in3()) {
    lowIndex = 3 * 600;
    highIndex = 4 * 600;
  } else if (in4()) {
    lowIndex = 4 * 600;
    highIndex = 5 * 600;
  } else if (in5()) {
    lowIndex = 5 * 600;
    highIndex = 6 * 600;
  } else if (in6()) {
    lowIndex = 6 * 600;
    highIndex = 7 * 600;
  } else if (in7()) {
    lowIndex = 7 * 600;
    highIndex = 8 * 600;
  } else if (in8()) {
    lowIndex = 8 * 600;
    highIndex = 9 * 600;
  } else if (in9()) {
    lowIndex = 9 * 600;
    highIndex = 10 * 600;
  } else if (in10()) {
    lowIndex = 10 * 600;
    highIndex = 11 * 600;
  } else if (in11()) {
    lowIndex = 11 * 600;
    highIndex = 12 * 600;
  } else if (in12()) {
    lowIndex = 12 * 600;
    highIndex = 13 * 600;
  } else if (in13()) {
    lowIndex = 13 * 600;
    highIndex = 14 * 600;
  } else if (in14()) {
    lowIndex = 14 * 600;
    highIndex = 15 * 600;
  } else if (in15()) {
    lowIndex = 15 * 600;
    highIndex = 16 * 600;
  } else if (in16()) {
    lowIndex = 16 * 600;
    highIndex = 17 * 600;
  } else if (in17()) {
    lowIndex = 17 * 600;
    highIndex = 18 * 600;
  } else if (in18()) {
    lowIndex = 18 * 600;
    highIndex = 19 * 600;
  } else if (in19()) {
    lowIndex = 19 * 600;
    highIndex = 20 * 600;
  } else if (in20()) {
    lowIndex = 20 * 600;
    highIndex = 21 * 600;
  } else if (in21()) {
    lowIndex = 21 * 600;
    highIndex = 22 * 600;
  } else if (in22()) {
    lowIndex = 22 * 600;
    highIndex = 23 * 600;
  } else if (in23()) {
    lowIndex = 23 * 600;
    highIndex = 24 * 600;
  } else if (in24()) {
    lowIndex = 0;
    highIndex = 24 * 600;
  }
}

//check if mouse is in button
boolean in0() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 100 && mouseY < 116.6);
}

//check if mouse is in button
boolean in1() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 116.6 && mouseY < 133.2);
}

//check if mouse is in button
boolean in2() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 133.2 && mouseY < 149.8);
}

//check if mouse is in button
boolean in3() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 149.8 && mouseY < 166.4);
}

//check if mouse is in button
boolean in4() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 166.4 && mouseY < 183);
}

//check if mouse is in button
boolean in5() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 183 && mouseY < 199.6);
}

//check if mouse is in button
boolean in6() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 199.6 && mouseY < 216.2);
}

//check if mouse is in button
boolean in7() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 216.2 && mouseY < 232.8);
}

//check if mouse is in button
boolean in8() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 232.8 && mouseY < 249.8);
}

//check if mouse is in button
boolean in9() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 249.8 && mouseY < 266);
}

//check if mouse is in button
boolean in10() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 266 && mouseY < 282.6);
}

//check if mouse is in button
boolean in11() {
  return (mouseX > 700 && mouseX < 750) && (mouseY > 282.6 && mouseY < 300);
}

//check if mouse is in button
boolean in12() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 100 && mouseY < 116.6);
}

//check if mouse is in button
boolean in13() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 116.6 && mouseY < 133.2);
}

//check if mouse is in button
boolean in14() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 133.2 && mouseY < 149.8);
}

//check if mouse is in button
boolean in15() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 149.8 && mouseY < 166.4);
}

//check if mouse is in button
boolean in16() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 166.4 && mouseY < 183);
}

//check if mouse is in button
boolean in17() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 183 && mouseY < 199.6);
}

//check if mouse is in button
boolean in18() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 199.6 && mouseY < 216.2);
}

//check if mouse is in button
boolean in19() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 216.2 && mouseY < 232.8);
}

//check if mouse is in button
boolean in20() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 232.8 && mouseY < 249.8);
}

//check if mouse is in button
boolean in21() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 249.8 && mouseY < 266);
}

//check if mouse is in button
boolean in22() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 266 && mouseY < 282.6);
}

//check if mouse is in button
boolean in23() {
  return (mouseX > 750 && mouseX < 800) && (mouseY > 282.6 && mouseY < 300);
}

//check if mouse is in button
boolean in24() {
  return (mouseX > 725 && mouseX < 750) && (mouseY > 325 && mouseY < 350);
}

//graphing algorithm
void graph(int startIndex, int endIndex) {
  float prevx, prevy, curx, cury, xScale;
  prevx = graphStart;  //only for first point
  prevy = graphBottom;
  xScale = map(1, 0, (endIndex - startIndex), 0, (graphEnd - graphStart));  //distance between points
  for (int sample = 0; sample < (endIndex - startIndex); sample++) {
    curx = prevx + xScale;  //increment xpos
    //find relate temp to range, then substract from bottom due to top to bottom grid
    cury = graphBottom - map(temps[sample], 0, 50, 0, (graphBottom - graphStart));
    line(prevx, prevy, curx, cury);  //draw line
    prevx = curx;
    prevy = cury;
  }
}

//process new data
void serialEvent (Serial myPort) {
  val = myPort.readStringUntil('\n');
  if (val != null) {
    val = trim(val);  //remove spaces
    temps[sampleNum] = Integer.parseInt(val);  
    //for debugging
    print(val);
    print(" ");
    println(sampleNum);
    //increment sample
    sampleNum++;
  }
}
