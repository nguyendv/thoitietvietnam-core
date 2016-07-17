#include "locations.h"

using namespace locations;
Location current(){
  // TODO: implement me!
  return Location();
}

Persistent* Persistent::getInstance(){
  if (instance_ == NULL)
    instance_ = new Persistent();
  return instance_;
}

Persistent::Persistent(){ 
  instance_ = NULL;
  init();
}

void Persistent::init(){
  // TODO: create table if not exists
}
