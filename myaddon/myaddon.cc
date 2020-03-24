#include <nan.h>
#include <iostream>

using namespace v8;

NAN_METHOD(Print) {
  std::cout << "I am a native addon and I AM ALIVE!" << std::endl;
  // info.GetReturnValue().Set()
}

NAN_METHOD(PrintArg) {
  auto arg = Nan::To<String>(info[0]);
  if (!arg.IsEmpty()) {
    auto strVal = arg.ToLocalChecked();
    std::cout << "I printed " << *String::Utf8Value(strVal) << std::endl;
  }
}

NAN_METHOD(StrLen) {
  Nan::HandleScope scope;
  auto arg = Nan::To<String>(info[0]);
  if (!arg.IsEmpty()) {
    auto strVal = arg.ToLocalChecked();
    auto len = strlen(*String::Utf8Value(strVal));
    auto retVal = Nan::New<Number>(len);
    info.GetReturnValue().Set(retVal);
  }
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("print").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(Print)).ToLocalChecked());
  Nan::Set(target, Nan::New("print_with_arg").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(PrintArg)).ToLocalChecked());
  Nan::Set(target, Nan::New("length").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(StrLen)).ToLocalChecked());
}

NODE_MODULE(myaddon, Init)
