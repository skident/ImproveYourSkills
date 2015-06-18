#include "QueryEngine.h"


QMap<QueryEngine::eCommands, QString> QueryEngine::mapTags =
{
    {cmdGetQuestion,        "QUESTION_GET"},
    {cmdAddQuestion,        "QUESTION_ADD"},
    {cmdEditQuestion,       "ADD_QUESTION"},
    {cmdDeleteQuestion,     "ADD_QUESTION"},
    {cmdCheckAnswer,        "ADD_QUESTION"},

};


QueryEngine::QueryEngine(QObject *parent) : QObject(parent)
{

}

