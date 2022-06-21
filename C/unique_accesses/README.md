Úkolem je vytvořit program, který bude zpracovávat logy a počítat unikátní návštěvy.

Předpokládáme že zaznamenáváme jednotlivé přístupy na WWW server. Zaznamenáváme uživatele, kteří přistupují - každý je označen jednoznačným identifikátorem. Identifikátor je celé číslo z uzavřeného intervalu 0 až 99999. Na vstupu jsou jednotlivé přístupy zadány v podobě příkazu + id, např.:

+ 123
+ 456
+ 123
+ 123
+ 789
Zde na pozici 0, 2 a 3 jsou přístupy uživatele 123, na pozici 1 je přístup uživatele 456, na pozici 4 pak přístup uživatele 789.
Ze zaznamenaných přístupů je potřeba vypočítat informaci o počtu unikátních uživatelů. Pro výpočet bude zadáno rozmezí, které má být analyzováno. Zadání má podobu ? from to, kde from a to jsou pozice od/do kterých máme unikátní uživatele počítat. Například pro ukázku by dotaz v podobě ? 0 4 dal odpověď 3 / 5 - 3 unikátní uživatelé z celkových 5 záznamů v dotazovaném rozmezí.

Vstupem programu jsou přístupy a dotazy, ty mohou být libovolně promíchané. Program zpracovává vstup, ukládá si informace o přístupech a průběžně odbavuje dotazy. Zpracování vstupu končí buď detekcí chyby (nesprávný vstup) nebo dosažením konce vstupu (EOF). Celkem je na vstupu nejvýše 1000000 přístupů, počet požadavků o výpočet unikátních přístupů není shora omezen.

Výstupem programu je reakce na každý vstup:

pro každý přístup program zobrazí, kolikátý přístup uživatele to je,
pro dotaz na počet unikátních přístupů program zobrazí informaci o počtu unikátních uživatelů v daném rozsahu / celkovém počtu přístupů ve vymezeném rozsahu.
Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu při přidání přístupu považujte:

chybí id uživatele,
id není celé číslo,
id není v intervalu < 0 ; 99999 >, nebo
přístupů je více než 1000000.
Za chybu v dotazu považujte:

chybí informace from a to,
from / to nejsou celá čísla,
from je menší než 0,
to je větší nebo roven počtu dosud zaregistrovaných přístupů, nebo
from je větší než to.
Chybou je rovněž situace, kdy na vstupu není ani přidání přístupu ani dotaz.

Ukázka práce programu:
Pozadavky:
+ 10
> prvni navsteva
+ 20
> prvni navsteva
+ 99999
> prvni navsteva
+ 5
> prvni navsteva
+ 20
> navsteva #2
+ 25
> prvni navsteva
+ 10
> navsteva #2
? 0 6
> 5 / 7
? 0 5
> 5 / 6
? 1 6
> 5 / 6
? 1 5
> 4 / 5
? 2 6
> 5 / 5
? 2 5
> 4 / 4
? 2 4
> 3 / 3
? 2 3
> 2 / 2
? 2 2
> 1 / 1
+ 5
> navsteva #2
+ 10
> navsteva #3
+ 5
> navsteva #3
+ 20
> navsteva #3
? 0 10
> 5 / 11
? 7 10
> 3 / 4
? 1 11
Nespravny vstup.
Pozadavky:
+ 10
> prvni navsteva
+ 20
> prvni navsteva
+ 30
> prvni navsteva
? 2 1
Nespravny vstup.
Pozadavky:
+ 12
> prvni navsteva
* 33
Nespravny vstup.