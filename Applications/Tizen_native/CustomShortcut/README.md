# CustomShortcut (tentative)

`CustomShortcut` is a nntrainer demo app that maps user defined symbol to any custom character by on-device training.

For example, user can draw `^^` few times to train a model to label the drawing as 😊.

Built and tested at `tizen studio 3.7` with `wearable-5.5 profile`

## How to Build and Run

You can use `tizen studio gui` to build and run.

If you want to do in CLI, you first need to [convert the project to CLI](https://developer.tizen.org/ko/development/tizen-studio/native-tools/cli/converting-projects-cli) and do as follows.

```bash
$ echo $(pwd)
/data/nntrainer/Applications/Tizen_native/CustomShortcut/
$ tizen build-native -a x86 -C Debug
# ...
$ tizen package -t tpk -- $(pwd)/Debug
WARNING: Default profile is used for sign. This signed package is valid for emulator test only.
Initialize... OK
Copying files... OK
Signing... OK
Zip path: /data/nntrainer/Applications/Tizen_native/CustomShortcut/Debug/org.example.nntrainer-custom-shortcut-0.0.1-x86.tpk
  adding: shared/       (in=0) (out=0) (stored 0%)
# ...
  adding: res/  (in=0) (out=0) (stored 0%)
total bytes=94664, compressed=35729 -> 62% savings
Zipping... OK
Package File Location: /data/nntrainer/Applications/Tizen_native/CustomShortcut/Debug/org.example.nntrainer-custom-shortcut-0.0.1-x86.tpk
# You need to prepare a device or emulator running before hand
$ tizen install -n "./Debug/org.example.nntrainer-custom-shortcut-0.0.1-x86.tpk" -t "W-5.5-circle-x86"
path is /home/owner/share/tmp/sdk_tools/tmp/org.example.nntrainer-custom-shortcut-0.0.1.tpk
# ...
spend time for pkgcmd is [343]ms

Tizen application is successfully installed.
Total time: 00:00:00.959
$ tizen run -p "org.example.nntrainer-custom-shortcut" -t "W-5.5-circle-x86"
result: App isnt running
... successfully launched pid = 24563 with debug 0
Tizen application is successfully launched.
```


