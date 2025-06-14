#include "parser.h"
#include <string.h>


QStringList *Parser::getScript()
 {
    return script;
}

void Parser::loadScript(const QString filename)
{
    if(script != NULL)
        delete script;

    script = readShiftJis(filename);
}

void Parser::loadScriptUTF8(const QString filename)
{
    if(script != NULL)
        delete script;

    // script = readShiftJis(filename);
    script = readUTF8(filename);
}

void Parser::prepareScript()
{
    int index;
    QString tag;
    QStringList *part;
    QStringList *tmp = new QStringList();

    while((index = script->indexOf(QRegExp("<part.+"))) != -1)
    {
        tag = script->at(index);
        script->removeAt(index);
        part = importPart(tag.section("filename=\"", 1).section("\"", 0, 0));

        if(part!=NULL)
        {
            tmp->append(*part);
            delete part;
        }

    }

    delete script;
    script = tmp;
}

QStringList *Parser::importPart(const QString filename)
{
    QFile f(filename);
    //QRegExp rx("(\n|\r)*");
    QStringList *part = new QStringList;

    if(f.exists())
    {
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QStringList tmp = QTextCodec::codecForName("Shift-JIS")->toUnicode(f.readAll().data()).split("\n");
        f.close();

        foreach(QString line, tmp) {
            if(!line.indexOf("#") == 0 && !line.contains("【"))
                part->append(line);
        }

        return part;
    }

    delete part;
    return NULL;
}

int Parser::writeShiftJis(const QString filename, const QStringList part)
{
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    f.write(QTextCodec::codecForName("Shift-JIS")->fromUnicode(part.join("\n")));
    f.close();

    return 0;
}

QStringList *Parser::readShiftJis(const QString filename)
{
    QStringList *file = new QStringList();

    QFile f(filename);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList tmp = QTextCodec::codecForName("Shift-JIS")->toUnicode(f.readAll().data()).split("\n");
    f.close();

    file->append(tmp);
    return file;
}

QStringList *Parser::readUTF8(const QString filename)
{
    QStringList *file = new QStringList();

    QFile f(filename);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    // QStringList tmp = QTextCodec::codecForName("Shift-JIS")->toUnicode(f.readAll().data()).split("\n");
    QStringList tmp = QTextCodec::codecForName("UTF-8")->toUnicode(f.readAll().data()).split("\n");
    f.close();

    file->append(tmp);
    return file;

}

int Parser::exportParts(const QString filename)
{
    loadScript(filename);

    QString tag;
    int startIndex, endIndex;
    while((startIndex = script->indexOf(QRegExp("<part.+"))) != -1)
    {
        tag = script->at(startIndex);
        script->removeAt(startIndex);

        if((endIndex = script->indexOf("</part>")) == -1)
            return -1;
        script->removeAt(endIndex);

        writeShiftJis(tag.section("filename=\"", 1).section("\"", 0, 0), script->mid(startIndex, endIndex));
    }

    return 0;
}

int Parser::dumpStrings(const char *in, const char *codec)
{
    QString in_file = in;
    QStringList *script_lines = readShiftJis(in_file);
    QStringList output;
    output.append("");

    int start_index = script_lines->indexOf("SCENE_PROLOGUE:");
    if(start_index == -1) start_index = 0;

    QString str_token = "pushstring ";
    for(int i = start_index +1; i < script_lines->length(); i++)
    {
        QString line = script_lines->at(i);

        if(line.contains("#") && line.contains("SPEAK"))
            output.append(parse_name(line.section("#", 1)));

        if(line.contains(str_token) && line.length() > str_token.length() + 1)
            output.append(line.section(str_token, 1) + "\n");
    }

    QTextCodec *cd = QTextCodec::codecForName(codec ? codec : "Shift-JIS");
    if (!cd) cd = QTextCodec::codecForName("Shift-JIS");
    QFile f(in_file.section(".", 0, 0) + "_strings.txt");
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    f.write(cd->fromUnicode(output.join("\n")));
    f.close();
    delete script_lines;
    return 0;
}

int Parser::convertFileEncoding(const QString &filename, const char *codec)
{
    if (!codec || strcmp(codec, "Shift-JIS") == 0)
        return 0;

    QStringList *lines = readShiftJis(filename);
    QTextCodec *cd = QTextCodec::codecForName(codec);
    if (!cd) cd = QTextCodec::codecForName("Shift-JIS");

    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    f.write(cd->fromUnicode(lines->join("\n")));
    f.close();
    delete lines;
    return 0;
}

QByteArray Parser::insertStrings(const QString strings, const QString script, int char_limit)
{
    // loadScript(strings);
    loadScriptUTF8(strings);
    prepareScript();
    QStringList *tl_lines = getScript();
    // QStringList *script_lines = readShiftJis(script);
    QStringList *script_lines = readUTF8(script);

    QStringList output;
    QString line, tmp;

    int start_index = script_lines->indexOf("SCENE_PROLOGUE:");
    if(start_index == -1) start_index = 0;
    output.append(script_lines->mid(0, start_index + 1));

    for(int i = start_index + 1; i < script_lines->length(); i++)
    {
        line = script_lines->at(i);

        if(line.contains("pushstring") && tl_lines->length() > 0)
        {
            tmp = line.section("pushstring ", 1);
            int index = -1;
            if(tmp.length() > 0)
                index = tl_lines->indexOf(tmp);
            if(index != -1 && tl_lines->at(index+1).length() > 0)
            {
                if(tl_lines->at(index+1).indexOf("@") == 0)
                    output.append("\tpushstring " + tl_lines->at(index+1).section("@", 1));
                else
                    output.append("\tpushstring " + wordWrap(tl_lines->at(index+1), line_limit, char_limit));

                tl_lines->removeAt(index);
                tl_lines->removeAt(index);
                tl_lines->removeAt(index);

                continue;
            }
            else
                output.append(line);
        }

        else
            output.append(line);
    }

    delete script_lines;
    // return QTextCodec::codecForName("Shift-JIS")->fromUnicode(output.join("\n"));
    QTextCodec *sjis = QTextCodec::codecForName("Shift-JIS");
    QTextCodec *gbk = QTextCodec::codecForName("GBK");

    QByteArray result;

    QList<QString>::Iterator it = output.begin(), itend = output.end();
    int cnt = 0;
    for (; it != itend; it++, cnt++) {
        // line = output.at(cnt);
        // if (line)
        // printf("output insert %s\n", line.toStdString().c_str());
        if (it->contains("@")) {
            QString tmp = *it;
            tmp = tmp.replace("@", "");
            result.append(gbk->fromUnicode(tmp));
            // printf("out ori %s\n", it->toStdString().c_str());
            // printf("out next %s\n", tmp.toStdString().c_str());
            // printf("out gbk %s\n", gbk->fromUnicode(tmp).toStdString().c_str());
        } else {
            result.append(sjis->fromUnicode(*it));
            // printf("out shift-jis %s\n", it->toStdString().c_str());
            // result.append(gbk->fromUnicode(*it));
        }
        result.append("\n");
    }
    return result;
}

const QString Parser::wordWrap(const QString str, int line_limit, int char_limit)
{
    QString line = str;
    int rest_size = str.length();
    int index = 0;

    while(--line_limit > 0 && rest_size > char_limit)
    {
        index = line.lastIndexOf(" ", index + char_limit);
        line.insert(index+1, "~");
        rest_size = line.length() - (index + 2);
    }

    return line;
}


QString Parser::parse_name(QString name_line)
{
    QString name = "【" + name_line.remove("　").remove(" ") + "】";
    return name;
}

Parser::~Parser()
{
    if(script != NULL)
        delete script;
}
