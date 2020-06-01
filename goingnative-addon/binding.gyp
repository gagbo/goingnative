{
  "targets": [
    {
      "target_name": "goingnative-addon",
      "sources": [ "goingnative-addon.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ],
  "conditions": [
    ['OS == "mac"', {
      'xcode_settings': {
        'MACOSX_DEPLOYMENT_TARGET': '10.9',
        'OTHER_CFLAGS': [
          '-std=c++11',
          '-stdlib=libc++'
        ],
        'OTHER_CPLUSPLUSFLAGS': [
          '-std=c++11',
          '-stdlib=libc++'
        ]
      }
    }]]
}
