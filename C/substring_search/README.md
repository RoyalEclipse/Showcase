Úkolem je vytvořit program, který bude vyhledávat zkratky (a tím vzdá hold nesmrtelné písni Ivana Mládka - nebo snad Zdeňka Svěráka).

Program dostane hledanou zkratku -- např. FIT. Zkratka je tvořena písmeny velké abecedy (A-Z). Po zadání zkratky následují zadání problémů s vyhledáním této zkratky. Zadání problému má dvě podoby:

? N "text"
nebo 
# N "text"
V uvozovkách může být zadaný libovolný text (neobsahuje odřádkování a uvozovky) a N je celé číslo. Program se pokusí vyhledat zadanou zkratku v textu. Při vyhledávání musí v textu identifikovat písmena zkratky (nerozlišujeme malá/velká písmena), pořadí písmen v textu musí odpovídat pořadí písmen ve zkratce a do každého slova v textu lze umístit nejvýše N písmen zkratky. Tedy například pro zkratku FIT a vstup:

# 1 "Faculty of Information Technology"
lze vybrat zkratku např. těmito způsoby:
"Faculty of Information Technology"
"faculty oF Information Technology"
"Faculty of informatIon Technology"
...
ale ne například takto:
"faculTy oF Information technology"
"Faculty of InformaTion technology"
v prvním případě není zachované pořadí písmen, ve druhém pak vybíráme 2 písmena ze slova Information, ale limit je N=1 písmeno.

Obecně lze zadanou zkratku nalézt v zadaném textu několika různými způsoby. Úkolem programu je vypočítat, kolika různými způsoby lze zkratku nalézt. Pokud je zadán problém ve tvaru:

? N "text"
očekává se, že program vyhledá zkratky podle popsaných pravidel a vypíše všechny nalezené možnosti. Ve výpisu program zdůrazní písmena ze zkratky (zobrazí je jako velká) a ostatní písmena z textu zobrazí jako malá. Nakonec připojí informaci o počtu nalezených možností.
Pokud je zadán problém ve tvaru:

# N "text"
pak program opět spočte možnosti, ale nevypisuje pozice jednotlivých nalezených zkratek. Pouze vypíše počet nalezených možností, jak lze zkratky do textu umístit. Navíc tyto počty určí pro limit 1, 2, 3, ..., N písmen zkratky maximálně umístěných do jednoho slova textu.
Vstup je zpracováván po řádkách. Na první řádce je zadaná hledaná zkratka, řádka nesmí obsahovat žádné další znaky navíc. Zkratka musí být zadaná velkými písmeny. Její délka není obecně omezená. Po zadání zkratky následuje zadání jednotlivých problémů -- textů k hledání. Formát problému je popsaný výše. Každý problém musí být zadán na jedné řádce. Program zpracovává problémy ze vstupu, dokud nedosáhne konce vstupu (EOF).

Výstupem programu je text s nalezenými pozicemi písmen zkratky a informace o počtu možností, kterými lze zkratku to textu umístit. Při výpisu textu s pozicemi písmen zkratky nezáleží na pořadí vypisovaných řádek. Formátování výstupu je zřejmé z ukázky níže.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

první řádka neobsahovala zkratku, zkratka byla prázdná (nulové délky) nebo se ve zkratce objevily jiné znaky než velká písmena,
nebyl rozpoznán problém k vyřešení (# a ?),
číslo N v zadání problému chybí, není platné, je nulové nebo záporné,
prohledávaný text není umístěn do uvozovek nebo nějaká uvozovka chybí.
Ukázka práce programu:
Zkratka:
FIT
Problemy:
? 1 "Faculty of Information Technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
> 4
? 2 "Faculty of Information Technology"
"Faculty of InformaTion technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF InformaTion technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
"faculty of inFormatIon Technology"
> 7
? 2 "FIT"
> 0
? 3 "FIT"
"FIT"
> 1
? 2   "Fibonacci   test"  
"FIbonacci   Test"
"FIbonacci   tesT"
"FibonaccI   Test"
"FibonaccI   tesT"
> 4
? 2   "  Fibonacci   test   "  
"  FIbonacci   Test   "
"  FIbonacci   tesT   "
"  FibonaccI   Test   "
"  FibonaccI   tesT   "
> 4