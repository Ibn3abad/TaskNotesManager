/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#include "Translator.h"

Translator::Translator(QObject *parent)
    : QObject(parent),
      m_language(QStringLiteral("de"))
{
    m_texts[QStringLiteral("de")] = {
        {"appTitle", "TaskNest 0.8"},
        {"tagline", "TaskNest - lokaler Task & Notes Manager"},
        {"filters", "Filter"},
        {"allTasks", "Alle Aufgaben"},
        {"open", "Offen"},
        {"inProgress", "In Arbeit"},
        {"done", "Erledigt"},
        {"highPriority", "Hohe Priorität"},
        {"tasks", "Aufgaben"},
        {"details", "Details"},
        {"menu", "Menü"},
        {"mobileReady", "Android-/Touch-Layout aktiv"},
        {"newTask", "Neue Aufgabe..."},
        {"add", "+ Hinzufügen"},
        {"delete", "Löschen"},
        {"noDescription", "Keine Beschreibung"},
        {"noTaskSelected", "Keine Aufgabe ausgewählt"},
        {"selectTaskHint", "Wähle links eine Aufgabe aus, um Notizen zu sehen."},
        {"status", "Status"},
        {"priority", "Priorität"},
        {"editTask", "Aufgabe bearbeiten"},
        {"description", "Beschreibung"},
        {"saveChanges", "Änderungen speichern"},
        {"newNote", "Neue Notiz"},
        {"title", "Titel"},
        {"notePlaceholder", "Notizinhalt in Markdown..."},
        {"saveNote", "Notiz speichern"},
        {"editMarkdown", "Bearbeiten"},
        {"previewMarkdown", "Vorschau"},
        {"markdownPreview", "Markdown-Vorschau"},
        {"markdownPreviewEmpty", "Noch kein Inhalt für die Vorschau."},
        {"markdownHelp", "Markdown ist aktiv: # Überschrift, - Liste, **fett**, `Code`, [Link](https://example.com)."},
        {"checklist", "Todo-Liste"},
        {"newTodo", "Neuer Todo-Punkt..."},
        {"addTodo", "+ Todo hinzufügen"},
        {"todoProgress", "Fortschritt"},
        {"todosOpen", "offen"},
        {"todosDone", "erledigt"},
        {"notes", "Notizen"},
        {"sqliteActive", "SQLite aktiv"},
        {"language", "Sprache"},
        {"about", "Über"},
        {"aboutTitle", "Über TaskNest"},
        {"aboutText", "TaskNest ist ein lokaler Task & Notes Manager auf Basis von C++, Qt Quick und SQLite.\n\nVersion: 0.8\nLizenz: MIT\nEntwickler: Ibn Abad Obayda\nGitHub: https://github.com/Ibn3abad/TaskNotesManager"},
        {"close", "Schließen"},
        {"low", "Niedrig"},
        {"medium", "Mittel"},
        {"high", "Hoch"},
        {"openValue", "open"},
        {"inProgressValue", "in_progress"},
        {"doneValue", "done"}
    };

    m_texts[QStringLiteral("en")] = {
        {"appTitle", "TaskNest 0.8"},
        {"tagline", "TaskNest - local task & notes manager"},
        {"filters", "Filters"},
        {"allTasks", "All tasks"},
        {"open", "Open"},
        {"inProgress", "In progress"},
        {"done", "Done"},
        {"highPriority", "High priority"},
        {"tasks", "Tasks"},
        {"details", "Details"},
        {"menu", "Menu"},
        {"mobileReady", "Android/touch layout active"},
        {"newTask", "New task..."},
        {"add", "+ Add"},
        {"delete", "Delete"},
        {"noDescription", "No description"},
        {"noTaskSelected", "No task selected"},
        {"selectTaskHint", "Select a task on the left to see its notes."},
        {"status", "Status"},
        {"priority", "Priority"},
        {"editTask", "Edit task"},
        {"description", "Description"},
        {"saveChanges", "Save changes"},
        {"newNote", "New note"},
        {"title", "Title"},
        {"notePlaceholder", "Note content in Markdown..."},
        {"saveNote", "Save note"},
        {"editMarkdown", "Edit"},
        {"previewMarkdown", "Preview"},
        {"markdownPreview", "Markdown preview"},
        {"markdownPreviewEmpty", "No content to preview yet."},
        {"markdownHelp", "Markdown is active: # Heading, - list, **bold**, `code`, [link](https://example.com)."},
        {"checklist", "Todo list"},
        {"newTodo", "New todo item..."},
        {"addTodo", "+ Add todo"},
        {"todoProgress", "Progress"},
        {"todosOpen", "open"},
        {"todosDone", "done"},
        {"notes", "Notes"},
        {"sqliteActive", "SQLite active"},
        {"language", "Language"},
        {"about", "About"},
        {"aboutTitle", "About TaskNest"},
        {"aboutText", "TaskNest is a local Task & Notes Manager built with C++, Qt Quick and SQLite.\n\nVersion: 0.8\nLicense: MIT\nDeveloper: Ibn Abad Obayda\nGitHub: https://github.com/Ibn3abad/TaskNotesManager"},
        {"close", "Close"},
        {"low", "Low"},
        {"medium", "Medium"},
        {"high", "High"},
        {"openValue", "open"},
        {"inProgressValue", "in_progress"},
        {"doneValue", "done"}
    };

    m_texts[QStringLiteral("ar")] = {
        {"appTitle", "TaskNest 0.8"},
        {"tagline", "TaskNest - مدير مهام وملاحظات محلي"},
        {"filters", "التصفية"},
        {"allTasks", "كل المهام"},
        {"open", "مفتوحة"},
        {"inProgress", "قيد التنفيذ"},
        {"done", "منجزة"},
        {"highPriority", "أولوية عالية"},
        {"tasks", "المهام"},
        {"details", "التفاصيل"},
        {"menu", "القائمة"},
        {"mobileReady", "تخطيط Android واللمس مفعّل"},
        {"newTask", "مهمة جديدة..."},
        {"add", "+ إضافة"},
        {"delete", "حذف"},
        {"noDescription", "لا يوجد وصف"},
        {"noTaskSelected", "لم يتم اختيار مهمة"},
        {"selectTaskHint", "اختر مهمة من القائمة لعرض ملاحظاتها."},
        {"status", "الحالة"},
        {"priority", "الأولوية"},
        {"editTask", "تعديل المهمة"},
        {"description", "الوصف"},
        {"saveChanges", "حفظ التغييرات"},
        {"newNote", "ملاحظة جديدة"},
        {"title", "العنوان"},
        {"notePlaceholder", "محتوى الملاحظة بصيغة Markdown..."},
        {"saveNote", "حفظ الملاحظة"},
        {"editMarkdown", "تحرير"},
        {"previewMarkdown", "معاينة"},
        {"markdownPreview", "معاينة Markdown"},
        {"markdownPreviewEmpty", "لا يوجد محتوى للمعاينة بعد."},
        {"markdownHelp", "Markdown مفعل: # عنوان، - قائمة، **غامق**، `كود`، [رابط](https://example.com)."},
        {"checklist", "قائمة المهام الفرعية"},
        {"newTodo", "عنصر جديد في القائمة..."},
        {"addTodo", "+ إضافة عنصر"},
        {"todoProgress", "التقدم"},
        {"todosOpen", "مفتوحة"},
        {"todosDone", "منجزة"},
        {"notes", "الملاحظات"},
        {"sqliteActive", "SQLite نشط"},
        {"language", "اللغة"},
        {"about", "حول"},
        {"aboutTitle", "حول TaskNest"},
        {"aboutText", "TaskNest هو مدير مهام وملاحظات محلي مبني باستخدام C++ و Qt Quick و SQLite.\n\nالإصدار: 0.8\nالرخصة: MIT\nالمطور: Ibn Abad Obayda\nGitHub: https://github.com/Ibn3abad/TaskNotesManager"},
        {"close", "إغلاق"},
        {"low", "منخفضة"},
        {"medium", "متوسطة"},
        {"high", "عالية"},
        {"openValue", "open"},
        {"inProgressValue", "in_progress"},
        {"doneValue", "done"}
    };
}

QString Translator::language() const
{
    return m_language;
}

void Translator::setLanguage(const QString &language)
{
    const QString normalized = language.toLower();
    if (!m_texts.contains(normalized) || normalized == m_language) {
        return;
    }

    m_language = normalized;
    emit languageChanged();
}

bool Translator::rtl() const
{
    return m_language == QStringLiteral("ar");
}

QString Translator::text(const QString &key) const
{
    const auto languageTexts = m_texts.value(m_language);
    if (languageTexts.contains(key)) {
        return languageTexts.value(key);
    }

    return m_texts.value(QStringLiteral("en")).value(key, key);
}
