#include "libreminesapptheme.h"

#include <QApplication>
#include <QPalette>
#include <QMessageBox>
#include <QStyleFactory>
#include <QDebug>
#include <QFile>

bool LibreMinesAppTheme::bSetApplicationTheme(const QString& theme)
{
    static bool firstTimeHere = true;

    bool restartNeeded = false;

    if(theme.compare("default", Qt::CaseInsensitive) == 0)
    {
        if(!firstTimeHere)
        {
            restartNeeded = true;
        }
    }
    else if(theme.compare("FusionDark", Qt::CaseInsensitive) == 0)
    {
        qApp->setStyleSheet("");
        qApp->setStyle(QStyleFactory::create ("Fusion"));
        QPalette palette;
        palette.setColor(QPalette::BrightText,      Qt::red);
        palette.setColor(QPalette::WindowText,      Qt::white);
        palette.setColor(QPalette::ToolTipBase,     Qt::white);
        palette.setColor(QPalette::ToolTipText,     Qt::white);
        palette.setColor(QPalette::Text,            Qt::white);
        palette.setColor(QPalette::ButtonText,      Qt::white);
        palette.setColor(QPalette::HighlightedText, Qt::black);
        palette.setColor(QPalette::Window,          QColor (53, 53, 53));
        palette.setColor(QPalette::Base,            QColor (25, 25, 25));
        palette.setColor(QPalette::AlternateBase,   QColor (53, 53, 53));
        palette.setColor(QPalette::Button,          QColor (53, 53, 53));
        palette.setColor(QPalette::Link,            QColor (42, 130, 218));
        palette.setColor(QPalette::Highlight,       QColor (42, 130, 218));

        qApp->setPalette(palette);
    }
    else if(theme.compare("FusionLight", Qt::CaseInsensitive) == 0)
    {
        qApp->setStyleSheet("");
        qApp->setStyle(QStyleFactory::create ("Fusion"));
        QPalette palette;
        palette.setColor(QPalette::BrightText,      Qt::cyan);
        palette.setColor(QPalette::WindowText,      Qt::black);
        palette.setColor(QPalette::ToolTipBase,     Qt::black);
        palette.setColor(QPalette::ToolTipText,     Qt::black);
        palette.setColor(QPalette::Text,            Qt::black);
        palette.setColor(QPalette::ButtonText,      Qt::black);
        palette.setColor(QPalette::HighlightedText, Qt::white);
        palette.setColor(QPalette::Window,          QColor (202, 202, 202));
        palette.setColor(QPalette::Base,            QColor (228, 228, 228));
        palette.setColor(QPalette::AlternateBase,   QColor (202, 202, 202));
        palette.setColor(QPalette::Button,          QColor (202, 202, 202));
        palette.setColor(QPalette::Link,            QColor (213, 125, 37));
        palette.setColor(QPalette::Highlight,       QColor (42, 130, 218));

        qApp->setPalette(palette);
    }
    else if(QStyleFactory::keys().contains(theme))
    {
        qApp->setStyleSheet("");
        qApp->setPalette(QPalette());
        qApp->setStyle(QStyleFactory::create(theme));
    }
    else
    {
        qApp->setPalette(QPalette());
        qApp->setStyle("");

        QString prefix;

        if(theme.compare("ConsoleStyle", Qt::CaseInsensitive) == 0)
            prefix = ":/qss/ConsoleStyle.qss";
        else if(theme.compare("NeonButtons", Qt::CaseInsensitive) == 0)
            prefix = ":/qss/NeonButtons.qss";
        else if(theme.compare("QDarkStyle", Qt::CaseInsensitive) == 0)
            prefix = ":/qdarkstyle/dark/style.qss";
        else if(theme.compare("QDarkStyleLight", Qt::CaseInsensitive) == 0)
            prefix = ":/qdarkstyle/light/style.qss";
        else if(theme.compare("BreezeDark", Qt::CaseInsensitive) == 0)
            prefix = ":/breeze/dark.qss";
        else if(theme.compare("BreezeLight", Qt::CaseInsensitive) == 0)
            prefix = ":/breeze/light.qss";


        QFile fileQSS(prefix);

        if (!fileQSS.exists())
        {
            qWarning() << "Unable to set stylesheet, file not found";
        }
        else
        {
            fileQSS.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&fileQSS);
            qApp->setStyleSheet(ts.readAll());
        }
    }

    firstTimeHere = false;

    return restartNeeded;
}
