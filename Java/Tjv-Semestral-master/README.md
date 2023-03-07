# Semestrální práce na BI-TJV 2022/2023
## E-Shop
Má semestrální práce bude mít formu jednoduchého e-shopu.

## Client-side implementace
Vytvořím jednoduchý front-end za pomocí Angularu a Bootstrapu.
Bude zobrazovat do gridu produkty které si může uživatel zakoupit, umožní možná filtrování podle ceny.
Dále bude k dispozici admin panel, který se po přihlášení uživatele se správnvými privilegii zpřístupní a umožní uživatelům přidávat kredity, za které mohou nakupovat.

## Business operace
Uživatel může vytvořit objednávku a "zakoupit" si nějáký produkt. Na straně serveru je potom zapotřebí vybrat správný sklad, odebrat uživateli kredity z účtu v hodnotě zakoupeného produktu a vytvořit objednávku.

## Komplexní dotaz navíc
Při tvorbě objednávky bych chtěl implementovat aby server odhadnul čas doručení. Client-side si vezme od uživatele kam má "doručit" tu objednávku. Server potom vybere nejbližší sklady které obsahují produkty které si uživatel objednal, spojí je leteckou čarou a spočítá čas doručení, pravděpodobně za pomocí BFS/Dijkstry. Předpokládejme že to bude hyper-moderní eshop co doručuje za pomoci dronů.

## Data model
![data model](/data-model.png "data model")

## Instukce ke spuštění a pro kontrolující

### Databáze
Databázi doporučuji spustit přes docker,
pro spuštění přes dockerfile:
    1) sudo docker build -t semestral .
    2) sudo docker run -d -p 5432:5432 --name semestral test

Manuální nastavení: postgres na portu `5432` s názvem `test`, uživatelem `test` a heslem `1234`.

### Front end
Front end se nacházi ve složce FrontEnd, je to jednoduchá stránka v html s bootstrapem.
Skládá se ze 3 stránek, mezi kterými lze přes header proklikávat.
Obsahuje hlavní stránku (landing.html) kde se dají "objednávat" předměty.
Dále obsahuje login a register, které slouží k získání svého userId a vytvoření nového uživatele.
POZOR nedělal jsem NIC s cookies nebo session, takže vaše id vám bude po registraci i přihlášení ukázáno a musíte jej poté manuálně zadat do objednávky
Také obsahuje odkaz Admin panel, který vás přesune na dokumentaci od springfoxu se swagger-ui.

### Back end
S trochou štěstí se spustí perfektně, na první pokus a bez toho aby jste museli něco upravovat. Je vytvořen v intelliJ a tam běží... minimálně na mojí straně. 

Business operace je v souborech pro SiteOrder, potom co přijde post request obsahující `SiteOrderRequest` tak se přesune do siteOrderService, kde je poté zpracován. Kontroluje se stav kreditů uživatele a tak podobně.

Ve WarehouseRepositoryCustomImpl se poté nachází dotaz navíc pro získání skladů pro vypočítání doby doručení.

## Dokumentace
Dokumentace je vytvořená přes springfox se swagger-ui, po spuštění je dostupná na `http://localhost:6060/swagger-ui.html`.
Je pro otestování lepší než můj front end, ale co už.

## Testy
Testy jsou obsaženy standartně ve složce Test.