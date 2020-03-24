#include <nan.h>
#include <iostream>

using namespace v8;

NAN_METHOD(Print) {
  std::cout << "I am a native addon and I AM ALIVE!" << std::endl;
  // info.GetReturnValue().Set()
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("print").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(Print)).ToLocalChecked());
}

NODE_MODULE(myaddon, Init)
