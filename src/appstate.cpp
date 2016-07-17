#include "appstate.h"
#include "locations.h"

AppState::AppState(){
  currLocationId = locations::current().Id;  
}

void AppState::onCurrentLocationChange(int newLocationID){

}
