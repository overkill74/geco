#include <iostream>
#include <string>
#include <list>

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#include <sqlite3.h>

#include "dbase/dbanagrafica.h"

using namespace std;


///
/// \brief test_create
///
static void test_create(const string& filename)
{
    xmlTextWriterPtr writer;
    writer = xmlNewTextWriterFilename(filename.c_str(), 0);
    xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);

    //
    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("root"));

    //
    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("AnagraficaUtenti"));

    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("Utente"));
    xmlTextWriterWriteFormatAttribute(writer, reinterpret_cast<const xmlChar *>("UID"), "%s", "jdnckjandvkjds");
    xmlTextWriterWriteFormatAttribute(writer, reinterpret_cast<const xmlChar *>("UID2"), "%d", 3);
    xmlTextWriterEndAttribute(writer);

    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Nome"), reinterpret_cast<const xmlChar *>("Ivan"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Cognome"), reinterpret_cast<const xmlChar *>("Zoli"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("email"), reinterpret_cast<const xmlChar *>("ivan@izstudio.it"));
    xmlTextWriterEndElement(writer);

    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("Utente"));
    xmlTextWriterWriteFormatAttribute(writer, reinterpret_cast<const xmlChar *>("UID"), "sdfgsdfgsdfg");
    xmlTextWriterEndAttribute(writer);

    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Nome"), reinterpret_cast<const xmlChar *>("Elisabetta"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Cognome"), reinterpret_cast<const xmlChar *>("Palermo"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("email"), reinterpret_cast<const xmlChar *>("eli@izstudio.it"));
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);

    //
    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("AnagraficaClienti"));

    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("Utente"));
    xmlTextWriterWriteFormatAttribute(writer, reinterpret_cast<const xmlChar *>("UID"), "jdnckjandvkjds");
    xmlTextWriterEndAttribute(writer);
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Nome"), reinterpret_cast<const xmlChar *>("Ivan"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Cognome"), reinterpret_cast<const xmlChar *>("Zoli"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("email"), reinterpret_cast<const xmlChar *>("ivan@izstudio.it"));
    xmlTextWriterEndElement(writer);

    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("Utente"));
    xmlTextWriterWriteFormatAttribute(writer, reinterpret_cast<const xmlChar *>("UID"), "sdfgsdfgsdfg");
    xmlTextWriterEndAttribute(writer);

    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Nome"), reinterpret_cast<const xmlChar *>("Elisabetta"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("Cognome"), reinterpret_cast<const xmlChar *>("Palermo"));
    xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar *>("email"), reinterpret_cast<const xmlChar *>("eli@izstudio.it"));
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);


    // root
    xmlTextWriterEndElement(writer);



    xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
}
///
/// \brief print_element_names
/// \param a_node
///
static void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            cout << "node type: Element, name: " << cur_node->name;
            if (cur_node->properties && cur_node->properties->name) {
                cout << " (" << cur_node->properties->name;
                if (cur_node->properties->children->content) {
                    cout << "=" << cur_node->properties->children->content;
                }
                cout << ")";
            }
            if (cur_node->children) {
                cout << " [" << cur_node->children->type << "]";
                if (cur_node->children->content) {
                    cout << " = " << cur_node->children->content;
                }
            }

            if (!xmlStrcmp(cur_node->name, reinterpret_cast<const xmlChar *>("Ivan"))) {
                cout << " *************";
            }

            cout << endl;
        }

        print_element_names(cur_node->children);
    }
}
///
/// \brief test_parse
/// \param filename
///
static void test_parse(const string& filename)
{
    xmlParserCtxtPtr ctxt; /* the parser context */
    xmlDocPtr doc; /* the resulting document tree */

    /* create a parser context */
    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
        fprintf(stderr, "Failed to allocate parser context\n");
        return;
    }
    /* parse the file, activating the DTD validation option */
    doc = xmlCtxtReadFile(ctxt, filename.c_str(), NULL, XML_PARSE_NOERROR/*XML_PARSE_DTDVALID*/);
    /* check if parsing succeeded */
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename.c_str());
    }
    else
    {
        /* check if validation succeeded */
        if (ctxt->valid == 0) {
            fprintf(stderr, "Failed to validate %s\n", filename.c_str());
        }
        else {
            xmlNode* root_element = xmlDocGetRootElement(doc);
            print_element_names(root_element);
        }

        /* free up the resulting document */
        xmlFreeDoc(doc);
    }
    /* free up the parser context */
    xmlFreeParserCtxt(ctxt);
}

///
/// \brief anagrafica_create
/// \param an
/// \param filename
///
static void anagrafica_create(const list<DbAnagrafica*>& an, const string& filename)
{
    xmlTextWriterPtr writer;
    writer = xmlNewTextWriterFilename(filename.c_str(), 0);
    xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);

    //
    xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar *>("Anagrafica"));

    for (auto& it: an) {
        it->writeToXml(writer);
    }

    xmlTextWriterEndElement(writer);

    xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
}

//////////////////////////////////////////////////////////////////////////////
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;

    cout << (const char*)data << endl;

    for (i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }

    cout << endl;
    return 0;
}

///
/// \brief execute_query
/// \param db
/// \param qry
///
static void execute_query(sqlite3* db, list<string>& out, const string& query)
{
    cout << query << endl;

    char* err_msg = nullptr;
    string cb_data("QUERY_TEST");
    int rc = sqlite3_exec(db
                          , query.c_str()
                          , callback
                          , const_cast<void*>(reinterpret_cast<const void*>(cb_data.c_str()))
                          , nullptr);
    if (rc != SQLITE_OK) {
        if (err_msg) {
            cout << "ERRORE: " << err_msg << endl;

            out.push_back(err_msg);
        }
    }
    sqlite3_free(err_msg);
}

///
/// \brief anagrafica_create_sql
/// \param an
/// \param filename
///
static bool anagrafica_create_sql(const list<DbAnagrafica*>& an, const string& filename)
{
    sqlite3* m_sq_db = nullptr;

    int rc = sqlite3_open(filename.c_str(), &m_sq_db);
    if (rc) {
        m_sq_db = nullptr;
        return false;
    }

    list<string> out;
    execute_query(
                m_sq_db, out,
                "CREATE TABLE Anagrafica ("
                "Id                INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT,"
                "Nome              TEXT,"
                "Cognome           TEXT,"
                "Telefono          TEXT,"
                "Numero            INTGER,"
                "Flag              BOOLEAN"
                ");"
    );

    int x=100;
    int y=100;
    for (auto& it: an) {
        execute_query(
                    m_sq_db, out,
                    "INSERT INTO Anagrafica "
                    "(Nome,Cognome,Telefono,Numero,Flag)"
                    " VALUES ("
                    "\"" + it->m_nome    + "\","
                    "\"" + it->m_cognome + "\","
                    "\"" + it->m_telefono + "\","
                    "" + to_string(x++) + ","
                    "\"" + "TRUEXX" + "\""
                    + ");"
        );
    }

    execute_query(
                m_sq_db, out,
                "SELECT * FROM Anagrafica;"
    );

    sqlite3_close(m_sq_db);
    return true;
}

///
/// \brief anagrafica_reader
/// \param an
/// \param filename
///
static void anagrafica_parser(list<DbAnagrafica*>& an, const string& filename)
{
    xmlParserCtxtPtr ctxt;
    xmlDocPtr doc;

    /* create a parser context */
    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
        fprintf(stderr, "Failed to allocate parser context\n");
        return;
    }
    /* parse the file, activating the DTD validation option */
    doc = xmlCtxtReadFile(ctxt, filename.c_str(), NULL, XML_PARSE_NOERROR/*XML_PARSE_DTDVALID*/);
    /* check if parsing succeeded */
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename.c_str());
    }
    else
    {
        /* check if validation succeeded */
        if (ctxt->valid == 0) {
            fprintf(stderr, "Failed to validate %s\n", filename.c_str());
        }
        else {
            xmlNode* root_element = xmlDocGetRootElement(doc);
            print_element_names(root_element);
        }

        /* free up the resulting document */
        xmlFreeDoc(doc);
    }
    /* free up the parser context */
    xmlFreeParserCtxt(ctxt);
}


///
/// \brief main
/// \return
///
int main()
{
    cout << "Hello World!" << endl;

    LIBXML_TEST_VERSION;

    list<DbAnagrafica*> m_anagrafica;

    DbAnagrafica ivan;
    DbAnagrafica eli;
    DbAnagrafica studio;


    ivan.m_uid                = "111";
    ivan.m_nome               = "Ivan";
    ivan.m_cognome            = "Zoli";
    ivan.m_resienza.via       = "Romagna";
    ivan.m_resienza.civico    = "37";
    ivan.m_resienza.cap       = "20092";
    ivan.m_resienza.citta     = "Cinisello Balsamo";
    ivan.m_resienza.provincia = "MI";
    ivan.m_codice_fiscale     = "ZLOVNI74A14F704B";
    ivan.m_nascita_data       = "14/01/1974";
    ivan.m_nascita_luogo.citta     = "Monza";
    ivan.m_nascita_luogo.provincia = "MI";
    ivan.m_telefono           = "3929352801";
    ivan.m_email              = "ivan@izstudio.it";
    ivan.m_pec                = "ivan.zoli@ingpec.eu";

    eli.m_uid                = "112";
    eli.m_nome               = "Elisabetta";
    eli.m_cognome            = "Palermo";
    eli.m_resienza.via       = "via XXV Aprile";
    eli.m_resienza.civico    = "54";
    eli.m_resienza.cap       = "20812";
    eli.m_resienza.citta     = "Limbiate";
    eli.m_resienza.provincia = "MB";

    studio.m_is_pg              = true;
    studio.m_uid                = "11";
    studio.m_nome               = "Studiozoli";
    studio.m_resienza.via       = "Romagna";
    studio.m_resienza.civico    = "37";
    studio.m_resienza.cap       = "20092";
    studio.m_resienza.citta     = "Cinisello Balsamo";
    studio.m_resienza.provincia = "MI";
    studio.m_codice_fiscale     = "ZLOVNI74A14F704B";
    studio.m_piva               = "05238880966";
    studio.m_codice_id          = "KRRH6B9";

    m_anagrafica.push_back(&ivan);
    m_anagrafica.push_back(&eli);
    m_anagrafica.push_back(&studio);

    //    anagrafica_create(m_anagrafica, "test3.xml");
    //    //test_create("test3.xml");
    //    //test_parse("test3.xml");
    //    list<DbAnagrafica*> m_anagrafica_r;
    //    anagrafica_parser(m_anagrafica_r, "test3.xml");

    anagrafica_create_sql(m_anagrafica, "test.db");


    return 0;
}
