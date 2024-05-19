# CDataframe

Description
-----------
Ce logiciel est conçu pour créer et manipuler des dataframes en langage C. 
> [!NOTE]
> Quand une fonction vous demande de renseigner des indices, ce sont bien les indices en langage naturel.   
> Plus précisemment le premier indice est 1.

-------------------------------------
Nous avons fait les choix suivants :
------------------
                                    1. Partie 1 : Dur 
                                    2. Partie 2 : Dur
                                    3. Partie 3 : Facile
Pour la partie 3 nous avons fait la section 8. "Fichier" 
et même si elle n'est pas incluse dans la partie 3 "Facile" nous avons juger bon de le mettre quand même.


Liste des Programmes
---------------------
1. create_cdataframe: Crée un nouveau dataframe.
2. delete_cdataframe: Supprime un dataframe existant.
3. delete_column_in_cdataframe: Supprime une colonne spécifique du dataframe.
4. get_cdataframe_cols_size: Retourne le nombre de colonnes dans le dataframe.
5. fill_cdataframe_user: Remplit le dataframe en demandant à l'utilisateur d'entrer les valeurs pour chaque colonne.
6. print_cdataframe: Affiche toutes les colonnes et leurs valeurs dans le dataframe.
7. printcol_cdataframe: Affiche une plage spécifique de colonnes dans le dataframe.
8. printlig_cdataframe: Affiche une plage spécifique de lignes dans le dataframe.
9. add_lig: Ajoute une ligne au dataframe.
10. del_lig: Supprime une ligne spécifique du dataframe.
11. add_col: Ajoute une colonne au dataframe.
12. del_col: Supprime une colonne spécifique du dataframe.
13. rename_col: Renomme une colonne spécifique du dataframe.
14. is_in_cdatafram: Vérifie si une valeur est présente dans le dataframe.
15. print_column_name: Affiche les noms des colonnes du dataframe.
16. nb_col: Compte le nombre de colonnes dans le dataframe.
17. nb_lig: Compte le nombre maximal de lignes dans le dataframe.
18. nb_equal_to: Compte le nombre de cellules égales à une valeur donnée dans le dataframe.
19. nb_superior_to: Compte le nombre de cellules supérieures à une valeur donnée dans le dataframe.
20. nb_inferior_to: Compte le nombre de cellules inférieures à une valeur donnée dans le dataframe.
21. replace_value_cdataframe: Remplace la valeur d'une cellule dans le dataframe.
22. load_from_csv: Charge les données d'un fichier CSV dans le dataframe.
23. export_cdataframe : Exporte les données du dataframe dans un fichier CSV.

Utilisation
-----------
Pour utiliser ces différentes fonctions, vous devez les appeler directement dans le programme principal. Notez que lorsque les fonctions attendent des pointeurs void, la valeur envoyée doit être du bon type avant d'être castée en (void*).

Exemple : Si vous souhaitez ajouter un entier dans une colonne de type entier, vous ne pouvez pas envoyer un pointeur de caractère casté en pointeur void.

Scénario d'utilisations
-----------------------
**create_cdataframe** :   
```
    ENUM_TYPE cdftype [] = {INT,INT};  
    CDATAFRAME *cdf = create_cdataframe(cdftype, 2);
```


**fill_cdataframe_user** :   
```
    ENUM_TYPE cdftype [] = {INT,INT};  
    CDATAFRAME *cdf = create_cdataframe(cdftype, 2);  
    fill_cdataframe_user(cdf);  
```

**fill_cdataframe_hard**
```
    ENUM_TYPE cdftype [] = {INT,DOUBLE};
    CDATAFRAME *cdf = create_cdataframe(cdftype, 2);
    int int_arr[] = {1, 2, 3};
    double double_arr[] = {1.1, 2.2, 3.3};
    void *tab[] = {int_arr, double_arr};
    int taille_tab[] = {3,3};
    fill_cdataframe_hard(cdf, tab, taille_tab, 2);
```
**export_cdataframe**
```
    ENUM_TYPE cdftype [] = {STRING,DOUBLE};
    CDATAFRAME *cdf = create_cdataframe(cdftype, 2);
    char* int_arr[] = {"Test", "2", "3"};
    double double_arr[] = {1.1, 2.2};

    void *tab[] = {int_arr, double_arr};
    int taille_tab[] = {3,2};

    fill_cdataframe_hard(cdf, tab, taille_tab, 2);
    char* name = "C:\\Users\\natha\\CLionProjects\\CDataframe\\export.csv";
    export_cdataframe(name,cdf);
```

**load_from_csv
```
    ENUM_TYPE type[] = {STRING,DOUBLE};
    char* name = "C:\\Users\\natha\\CLionProjects\\CDataframe\\export.csv";
    CDATAFRAME *cdf = load_from_csv(name,  type, 2);
```


