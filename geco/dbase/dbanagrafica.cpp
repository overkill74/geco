#include "dbanagrafica.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#define XML_CHAR(txt) reinterpret_cast<const xmlChar *>(txt)


//-------------------------------------------------------------
DbAnagrafica::DbAnagrafica()
    : m_is_pg(false)
{

}

//-------------------------------------------------------------
void DbAnagrafica::write_element(xmlTextWriterPtr& out_xml, const string& name, const string& val)
{
    if (val.empty()) {
        return;
    }
    xmlTextWriterWriteElement(out_xml, XML_CHAR(name.c_str()), XML_CHAR(val.c_str()));
}
//-------------------------------------------------------------
void DbAnagrafica::write_element(xmlTextWriterPtr& out_xml, const string& name, const bool val)
{
    write_element(out_xml, name, string(val ? "true" : "false"));
}
//-------------------------------------------------------------
void DbAnagrafica::write_element(xmlTextWriterPtr& out_xml, const string& name, const Indirizzo& val)
{
    xmlTextWriterStartElement(out_xml, XML_CHAR(name.c_str()));
    write_element(out_xml, "via"      , val.via      );
    write_element(out_xml, "civico"   , val.civico   );
    write_element(out_xml, "cap"      , val.cap      );
    write_element(out_xml, "citta"    , val.citta    );
    write_element(out_xml, "provincia", val.provincia);

    xmlTextWriterEndElement(out_xml);
}

//-------------------------------------------------------------
bool DbAnagrafica::writeToXml(xmlTextWriterPtr& out_xml)
{
    xmlTextWriterStartElement(out_xml, XML_CHAR("Soggetto"));
    xmlTextWriterWriteFormatAttribute(out_xml, XML_CHAR("UID"), "%s", m_uid.c_str()); xmlTextWriterEndAttribute(out_xml);

    //    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Nome"), reinterpret_cast<const xmlChar *>("Ivan"));
    //    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Cognome"), reinterpret_cast<const xmlChar *>("Zoli"));
    //    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("email"), reinterpret_cast<const xmlChar *>("ivan@izstudio.it"));


    //    bool            m_is_pg;            //! Persona giuridica
    write_element(out_xml, "Nome"     , m_nome           );
    if (!m_is_pg) {
        write_element(out_xml, "Cognome"  , m_cognome        );
        write_element(out_xml, "N_Data"   , m_nascita_data   );
        write_element(out_xml, "N_Luogo"  , m_nascita_luogo  );
    }
    write_element(out_xml, "Residenza", m_resienza       );
    write_element(out_xml, "CF"       , m_codice_fiscale );
    write_element(out_xml, "PIVA"     , m_piva           );
    write_element(out_xml, "Telefono" , m_telefono       );
    write_element(out_xml, "Email"    , m_email          );
    write_element(out_xml, "Pec"      , m_pec            );
    write_element(out_xml, "CodId"    , m_codice_id      );

    xmlTextWriterEndElement(out_xml);

    return false;
}

