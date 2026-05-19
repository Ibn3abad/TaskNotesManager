# Android Build Notes

Diese Version ist für Android vorbereitet.

## Benötigt

- Qt Creator
- Qt 6.5+ mit Android-Komponenten
- Android SDK
- Android NDK passend zur installierten Qt-Version
- JDK
- Android-Gerät mit USB-Debugging oder Emulator

## Build

Am einfachsten über Qt Creator:

1. `CMakeLists.txt` öffnen.
2. Android-Kit auswählen.
3. Konfigurieren lassen.
4. Build/Run drücken.

## Warum kein eigener AndroidManifest-Template?

Qt kann für einfache Qt-Quick-Apps die Android-Paketstruktur automatisch erzeugen.

