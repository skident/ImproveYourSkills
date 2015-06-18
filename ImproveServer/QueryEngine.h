#pragma once

#include <QObject>
#include <QMap>

class QueryEngine : public QObject
{
    Q_OBJECT

public:
//    enum eExceptions
//    {

//    };

    /**
     * @brief The eCommands enum
     */
    enum eCommands
    {
        cmdQuestion,
        cmdAnswer,
        cmdUser,
        cmdGroup,
        cmdSettings,
    };

    enum eActions
    {
        actAdd,
        actEdit,
        actEdited,
        actDelete,
        actGet,
        actList,
        actCheck,
        actShow,
    };

    static QMap<eCommands, QString> mapTags;

    explicit QueryEngine(QObject *parent = 0);

    void Parse();
signals:

public slots:
};

