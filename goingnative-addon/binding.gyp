{
  "targets": [
    {
      "target_name": "goingnative-addon",
      "sources": [ "goingnative-addon.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
