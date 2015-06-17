#ifndef XML_ENGIE_CLIENT_H
#define XML_ENGIE_CLIENT_H

#include "xml_engie_client_global.h"

#include "QtXml"
#include "memory"
#include "memory.h"
#include "QSharedpointer.h"
#include "map"
#include "string"
#include "string.h"
#include "QString"
#include "QVector"
#include "QVector.h"

typedef enum
{
    eViewName           =1,
    eTextMsgTop         =2,
    ButtomAnswerPos1    =3,
    ButtomAnswerPos2    =4,
    ButtomAnswerPos3    =5,
    ButtomAnswerPos4    =6,
    eEnd

} eTags;
typedef std::map<eTags,std::string> TMap;
std::vector<std::string> TagNameList{"ViewName",
                                       "TextMsgTop",
                                       "imgTop",
                                       "ButtomAnswerPos1",
                                       "ButtomAnswerPos2",
                                       "ButtomAnswerPos3",
                                       "ButtomAnswerPos4"
                                      };

class XML_ENGIE_CLIENTSHARED_EXPORT XML_Engie_Client
{

public:
    XML_Engie_Client();
    void setXMLBuff(char * data);
    void setXMLBuff(QString & sData);
    void setXMLBuff(QByteArray bArray);

    void setTagMap();

    // hardcoded methods for tests


    void hardCodeInit();

    // hardcoded methods for tests
    void getTaskList();

    // hardcoded methods for tests


private:
   // std::shared_ptr<QXmlStreamReader> m_SheredPointer_XML_Data;
    QXmlStreamReader *m_Pointer_XML_Data;
    TMap TagMap;
    std::vector<int> m_TaskList;
};

#endif // XML_ENGIE_CLIENT_H


//<xml>
//	<ViewName>Oops!!!</ViewName>
//	<TextMsgTop>How many bytes  in long?</TextMsgTop>
//	<imgTop>buffer with data</imgTop>
//	<ButtomAnswerPos1>1</ButtomAnswerPos1>
//	<ButtomAnswerPos2>2</ButtomAnswerPos2>
//	<ButtomAnswerPos3>4</ButtomAnswerPos3>
//	<ButtomAnswerPos4>8</ButtomAnswerPos4>
//</xml>
