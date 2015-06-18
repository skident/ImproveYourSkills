#include "xml_engie_client.h"



XML_Engie_Client::XML_Engie_Client()
{
}
void XML_Engie_Client::setXMLBuff(char *data)
{
    m_Pointer_XML_Data = new QXmlStreamReader(data);
}
void XML_Engie_Client::setXMLBuff(QString & sData)
{
    m_Pointer_XML_Data = new QXmlStreamReader(sData);
}
void XML_Engie_Client::setXMLBuff(QByteArray bArray)
{
    m_Pointer_XML_Data = new QXmlStreamReader(bArray);
}

void XML_Engie_Client::hardCodeInit()
{
    eTags i = eViewName;
    while(i!=eEnd)
    {
        TagMap[i] = TagNameList[i];
    }

}

void XML_Engie_Client:: getTaskList()
{


    while (!m_Pointer_XML_Data->atEnd() && !m_Pointer_XML_Data->hasError())
    {
            auto iter = TagMap.find(m_Pointer_XML_Data->name()); //TODO how convert qstringf intro string , still a qwestion
            if ( iter!= TagMap.end())
                m_TaskList.push_back(iter.second);
            m_Pointer_XML_Data->readNext();

    }

}

//void XML_Engie_Client::setXMLBuff(char * data)
//{
//    QXmlStreamReader xml(

//}
