#include <nan.h>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#endif

using namespace v8;

// A worker class extending the NanAsyncWorker helper
// class, a simple encapsulation of worker-thread
// logic to make simple tasks easier

class MyWorker : public Nan::AsyncWorker {
 public:
  // Constructor
  MyWorker(Nan::Callback *callback, int delay)
    : Nan::AsyncWorker(callback), delay(delay) {}
  // Destructor
  ~MyWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
#ifdef _WIN32
  Sleep(delay);
#else
  usleep(delay * 1000);
#endif
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    Nan::HandleScope scope;

    // Nan::Callback#Call() does a Nan::MakeCallback() for us
    callback->Call(0, NULL);
  }

 private:
  int delay;
};

NAN_METHOD(Delay) {
  // get delay and callback
  Nan::HandleScope scope;
  auto msDelay = Nan::To<int>(info[0]);
  auto delay = msDelay.FromJust();
  auto callback = info[1].As<Function>();

  // create NanCallback instance wrapping the callback
  auto nanCallback = new Nan::Callback(callback);
  // create a MyWorker instance, passing the callback and delay
  auto worker = new MyWorker(nanCallback, delay);
  // queue the worker instance onto the thread-pool
  Nan::AsyncQueueWorker(worker);
}

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
  Nan::Set(target, Nan::New("delay").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(Delay)).ToLocalChecked());
}

NODE_MODULE(myaddon, Init)
