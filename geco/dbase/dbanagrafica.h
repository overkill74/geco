///
/// \brief Anagrafica
///

#ifndef DBANAGRAFICA_H
#define DBANAGRAFICA_H

#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

using namespace std;

///
/// \brief The DbAnagrafica class
///
class DbAnagrafica
{
public:
    struct Indirizzo {
        string      via;                //! via
        string      civico;             //! civico
        string      cap;                //! cap
        string      citta;              //! citta'
        string      provincia;          //! Provincia
    };

public:
    DbAnagrafica();

    ///
    /// \brief writeToXml
    /// \param out_xml
    /// \return success
    ///
    bool writeToXml(xmlTextWriterPtr& out_xml);

private:
    ///
    /// \brief write_element
    /// \param out_xml
    /// \param name
    /// \param val
    ///
    void write_element(xmlTextWriterPtr& out_xml, const string& name, const string& val);
    void write_element(xmlTextWriterPtr& out_xml, const string& name, const bool val);
    void write_element(xmlTextWriterPtr& out_xml, const string& name, const Indirizzo& val);

public:
    bool            m_is_pg;            //! Persona giuridica
    string          m_uid;              //! Unique id
    string          m_nome;             //! Nome o denominazione
    string          m_cognome;          //! Cognome
    string          m_codice_fiscale;   //! Codice Fiscale
    Indirizzo       m_resienza;         //! Residenza
    string          m_piva;             //! Partita Iva
    string          m_nascita_data;     //! Data di nascita
    Indirizzo       m_nascita_luogo;    //! Luogo di nascita
    string          m_telefono;         //!
    string          m_email;            //!
    string          m_pec;              //!
    string          m_codice_id;        //!
};

#endif // DBANAGRAFICA_H
