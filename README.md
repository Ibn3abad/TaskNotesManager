# TaskNotesManager / TaskNest v0.8

TaskNest ist ein lokaler Task & Notes Manager mit C++, Qt Quick/QML und SQLite.

## Funktionen

- Desktop-Layout für Linux, Windows und macOS
- Android-/Touch-Layout mit Drawer und Tabs
- Aufgaben erstellen, auswählen, bearbeiten und löschen
- Filter: Alle, Offen, In Arbeit, Erledigt, Hohe Priorität
- Todo-Checklisten innerhalb jeder Aufgabe
- Markdown-Notizen mit Vorschau
- SQLite-Persistenz im systemeigenen App-Datenordner
- Internationalisierung: Deutsch, Englisch, Arabisch
- Arabisch mit RTL-Layout
- About-Dialog

## Desktop Build, z. B. Linux Mint

```bash
cmake -B build -S .
cmake --build build
./build/appTaskNotesManager
```

## Android Build mit Qt Creator

1. Qt Maintenance Tool öffnen.
2. Eine Qt-Version mit **Android**-Komponenten installieren, z. B. Qt 6.5+ oder neuer für Android.
3. Android SDK, Android NDK, JDK und CMake in Qt Creator konfigurieren.
4. Projekt `CMakeLists.txt` in Qt Creator öffnen.
5. Als Kit ein Android-Kit wählen, z. B. `Android Qt 6.x Clang arm64-v8a`.
6. Build starten.
7. Auf Emulator oder verbundenem Android-Gerät ausführen.

## Android-Anpassungen in v0.8

- Das Hauptfenster nutzt auf Android Fullscreen.
- Das feste Desktop-Minimum wurde auf Android deaktiviert.
- Bei kleinen Bildschirmen wird automatisch ein mobiles Layout genutzt.
- Die Sidebar liegt im mobilen Layout in einem Drawer.
- Aufgaben und Details/Notizen liegen im mobilen Layout in Tabs.
- SQLite nutzt `QStandardPaths::AppDataLocation`, damit der Datenbankpfad auf Android, Linux, Windows und macOS korrekt ist.
- CMake enthält Android-Metadaten wie Version Code, Version Name und Minimum SDK.

## Hinweis

Für Android wird aus dem gleichen C++/QML-Code eine APK/AAB gebaut.
