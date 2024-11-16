
## /e/ OS

settings put global captive_portal_http_url http://204.ecloud.global
settings put global captive_portal_https_url https://e.foundation/net_204/

## change ntp

settings put global ntp_server pool.ntp.org

## DeBlot pre-installed apps

1. Use this command to list all the apps installed

    ```
    adb shell pm list packages
    ```

- To search any particular keyword use `grep` command
    ```
    adb shell pm list packages | grep 'keyword'
    ```
- Package names will be somewhat like this, eg. for `Google Assistant` its `com.android.hotwordenrollment.okgoogle`, for `Google Auto` its `com.google.android.projection.gearhead`


2. Copy the name of the package you want to uninstall and use the following command

    ```
    adb shell pm uninstall -k --user 0 com.my.demo.app
    ```

> To undo the changes:
> ```
>adb shell cmd package install-existing com.my.demo.app
> ```
