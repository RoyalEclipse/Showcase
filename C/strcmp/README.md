Úkolem je realizovat funkci (ne program, pouze funkci), která bude porovnávat dvojici řetězců, zda jsou tvořeny ze stejných slov.

Požadovaná funkce sameWords má rozhraní podle ukázky níže:

int sameWords ( const char * a, const char * b );
Parametry jsou dva řetězce, které funkce porovná. Parametry jsou určené pouze pro čtení (const), funkce je nesmí měnit.

Návratovou hodnotou funkce je hodnota 1 (shoda) nebo 0 (neshoda). Za shodu považujeme, pokud jsou oba řetězce tvořené stejnými slovy. Tedy pokud je každé slovo z prvního řetězce alespoň jednou obsaženo ve druhém řetězci a naopak. Při porovnávání slov nerozlišujeme malá a velká písmena.

Slova jsou tvořena znaky, pro které funkce isalpha vrací nenula. Ostatní znaky považujte za oddělovače slov.

Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce sameWords. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z sameWords volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci sameWords (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů "zmizí", tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující v povinných testech může získat nominálních 100% bodů. Bonusový test vyžaduje časově efektivní výpočet i pro dlouhé řetězce obsahující mnoho slov.

