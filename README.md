
# Software GeCo
Gestione Commesse

## Definizioni
- *Committente* è colui che ci commissiona il lavoro
- *Cliente* è il committente del nostro committente (che potrebbero coincidere) 
- *Attività* è la singola operazione da eseguire. Una attività può essere facoltativa o mandataria. Una attività è composta da serie di Task
- *Task* 
- *Lavorazione* è la serie delle singole attività
- *Data acquisizione* è la data in cui il lavoro è astato commissionato
- *Scadenza intermedia* è la di scadenza di una attività
- *Scadenza chiusura lavori* è la scadenza dell'ultima attività in ordine di scadenza

## Specifiche

### Gestire anagrafica clienti
- Dividendo in clienti e committenti

### Anagrafica edifici
- Dati catastali 

### Stato avanzamento lavori
- Per Elisabetta.
- Per Ivan.
- Data in lavori e le scadenze intermedie.
- Stato pagamento (preventivato, fatturato etc)

### Inviare alert
Sullo stato lavori, da definire come

### Stampare un report
- Sullo stato dei lavori, potendo filtrare per cliente / committente.
- In ordine di scadenza per le urgenze.
- Il report deve avere i link alla cartella / file

### Lavorazione
- Assegnare Lavorazione con modello predefinito
 - Super-bonus
 - APE 
 - etc...
 - Definire modelli con elenco attività
 - Manualmente
- Campo note

### Attività
- Preventivo
- Lettera di incarico
- Addendum
- Verbale sopralluogo
- Documentazione
 - Ricerca piante catastali
 - Documentazione cliente
   - Documenti
   - Residenza
   - Recapiti
 - Piantine
 - Fotografie
 - Visure
 - Documentazione tecnica sulle componenti (muri, finestre, impianti etc)
- Link alla varia documentazione
- Stato pagamento (preventivato, fatturato etc)

### Archivio Datasheet
- Per tipo / modello e altro da definire

### Dettagli software
- Database su file di testo per poter permettere la gestione con SVN o comunque un merge delle informazioni.



