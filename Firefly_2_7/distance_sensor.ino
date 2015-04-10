int value_distance_sensor_one;



int getMeasurement_sensor_one()
{
  // Request a distance reading from the URM37
  switch(urm.requestMeasurementOrTimeout(DISTANCE, value_distance_sensor_one)) // Find out the type of request
  {
  case DISTANCE: // Double check the reading we recieve is of DISTANCE type
    //    Serial.println(value); // Fetch the distance in centimeters from the URM37
    return value_distance_sensor_one;
    break;
  case TEMPERATURE:
    return value_distance_sensor_one;
    break;
  case ERROR:
    
    break;
  case NOTREADY:
   // Serial.println("Not Ready");
    break;
  case TIMEOUT:
  //  Serial.println("Timeout");
    break;
  } 

  return -1;
}
