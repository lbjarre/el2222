//Assuming that command format is ' cmd : sub_cmd value ' or ' cmd : sub_cmd '
//Read the serial data received from the Rpi and parse it for various commands
void readSerialCmd(){
  String inCmd = "";
  String inValue = "";
  String inSubCmd = "";
  bool subCmdPresent = false;
  short int valueCount = 0;
  int values[5];
  values[0]=22;
  while(Serial.available() > 0){
    int inChar = Serial.read();
    if (isDigit(inChar)){
      inValue += (char)inChar;
    }
    else if(isSpace(inChar) || inChar == '\n'){
      // Ignore for now
    }
    else if( inChar == ':' ){
      subCmdPresent = true;
    }
    else if( inChar == ',' ){
      if (inValue != ""){
        values[valueCount] = inValue.toInt();
      }
      inValue = "";
      valueCount++;
    }
    else if(isAscii(inChar)){
      if(subCmdPresent){
        inSubCmd += (char)inChar;
      }
      else{
        inCmd += (char)inChar;
      }
    }

    if (inChar == '\n'){
      if (inValue != ""){
        values[valueCount] = inValue.toInt();
      }
      interpretSerialCmd(inCmd,inSubCmd,&values[0]);
    }
  }
}

// Interpet the meaning of the commands received previously and respond accordingly.
void interpretSerialCmd(String cmd,String subCmd, int* values)
{

  if ( (String)"Hi.Arduino" == cmd ){
    Serial.println("Hi.Raspberry");
  } 
  else if ((String)"set.value" == cmd){
    if ((String)"lin_vel" == subCmd){
        //Implement function to set Linear velocity
        //Set values are passed back for debug
        Serial.println(values[0]);
    }
    else if ((String)"ang_vel" == subCmd){
        //Implement function to set angular velocity
        //Set values are passed back for debug
        Serial.println(values[0]);
    }
    else{
        Serial.println("!!! error !!!!");
    }
  }
  
  else if ((String)"get.value" == cmd){
        Serial.println("!!! Implementation incomplete !!!!");
  }
  else{
    Serial.println("Cmd_Error");
  }
}
