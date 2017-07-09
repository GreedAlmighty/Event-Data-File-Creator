#ifndef TEXTEDITS_H
#define TEXTEDITS_H

#include <QString>

#define HEADERS 1
#define NO_HEADERS 0

class TextEdit
{
public:
    TextEdit();
    ~TextEdit();
    void editTextLine( QString line );

private:
    void createGroupId(int chipcode_length, QString *csv_line );
};

#endif // TEXTEDITS_H
