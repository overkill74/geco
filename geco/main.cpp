#include <iostream>
#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

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
/// \brief main
/// \return
///
int main()
{
    cout << "Hello World!" << endl;

    LIBXML_TEST_VERSION;

    test_create("test3.xml");
    test_parse("test3.xml");

    return 0;
}
