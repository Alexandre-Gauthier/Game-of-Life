## READ ME pour le projet #1 du cours B62
### Projet : Game of Life
### Réalisé par : Alexandre Gauthier, Hugo Turgeon, William Frazilien et Joey Dallaire

#### Quelle(s) est(sont) la(les) classe(s) qui s’occupe(nt) de faire la gestion du fichier d’entré ?

La classe RLEReader (RLEReader.h et RLEReader.cpp).

#### Êtes-vous capable de gérer les erreurs de fichiers mentionné?

Nous sommes capable de gérer les erreurs de fichiers mentionnés.

Tout d'abord, l'entête est validée et reconnue seulement lorsqu'elle commence par un '#' suivi
d'un des 6 caractères acceptés pour l'entête, soit : 'C', 'c', 'N', 'O', 'R' et 'r'

De plus, le lecteur de fichier RLE fonctionne lorsqu'il y a entre 0 et n nombre de ligne sans aucun problème.
Il va continuer à ignorer les lignes tant qu'elles sont conforme à la syntaxe d'une ligne de commentaire.

Une fois une ligne non commentaire rencontrée, le lecteur va vérifié la présence de la ligne de transition.
Dans le cas où elle est absente, le fichier sera considéré non conforme et donc ignoré.
Cette vérification se fais à l'aide d'un regex qui vérifie à la fois la syntaxe de la ligne
et la présence de taille positive pour la valeur du x et du y. En effet, le regex n'accepte pas
des tailles de x et y négatif.

Dans le cas où il y a une erreur dans le fichier RLE et que la taille en x ou en y spécifiée est dépassée,
le lecteur de fichier RLE va ignorer les caractères en trop. De plus, il va retourner au model que le fichier
n'est pas conforme.

Le caractère de fin de séquence, soit le '!' est validé et un booléen nommé 'mFileOver' est mis
à vrai pour signifier que la fin du fichier est atteint afin d'arrêter la lecture de celui-ci.

Lorsque le fichier est considéré comme non conforme, une génération aléatoire sera effectuée à la place
dont le pourcentage sera le dernier pourcentage utilisé par le programme (0.15 par défaut).
 

#### Où se trouve dans votre code l’endroit où spécifiez le dossier où se trouve les fichiers RLE?

Le chemin du dossier contenant les fichiers RLE est spécifié dans une variable de classe du model
nommée 'mRLEPath'. Celle-ci est directement déclarée dans le header.

### Ajout Personnel

#### Quels étaient les intentions initiales?

Au départ, nous voulions implémenter un système d'espèce multiples en plus du système de base à seulement 2 états.
La différenciation des états à l'écran serait faite avec l'utilisation des couleurs disponibles dans les outils de la console.

L'état 0 représente les cellules inactives alors que les états suivants (2 à 7) représentent différentes espèces. Les touches
'+' et '-' permettent d'ajouter dynamiquement des espèces, générant une règle de vie aléatoirement et regénérant aléatoirement
l'espace avec les nouvelles espèces. Notre code permettrait normalement un nombre infini d'espèce mais, la console ne pouvant 
afficher que 6 couleurs, nous avons décider de limité la quantité d'espèces à 6. 

Afin de rendre plus intéressant l'interaction entre les espèces, nous avons ajouté un paramètre supplémentaire à la règle, Die. 
Ce paramètre regarde la quantité d'individus d'une autre espèce que celle de la cellule observée.

Puisque nous devions gérer la modification de couleur des cellules actives et la gestion de règles particulières (Game of Life,
High Life, Day & Night), nous avons décidé que ces paramètres ne s'appliquerait que sur la première espèce. Ainsi, cette espèce
devient donc un barème sur lequel nous pouvons comparer les règles aléatoires des espèces supplémentaires.

De plus, puisqu'à chaque nouvelle génération de l'espace les règles des espèces supplémentaires sont regénérées, nous avons ajouté
la touche 'v' afin de refaire une génération en gardant les mêmes règles.


#### Qu’est-ce qui fonctionnent bien?
Nous sommes particulièrement satisfait des résultats amenés par l'interaction entre les différentes espèces et les scénarios 
émergents de la génération aléatoire des règles. 

#### Qu’est-ce qui fonctionnent moins bien?
Nous avons été obligé de faire des compromis auprès de l'application des règles afin de simplifier cet aspect. Ainsi, les dernières 
règles du vecteur de règles ont priorité sur la propriété Born, donnant ainsi un avantage aux dernières espèces créées.


#### Que pourrions-nous ajouter?
Après avoir monté ce système, il serait intéressant de simuler une évolution en générant des règles à partir des espèces 
survivantes de la simulation précédente.


### Selon vous, quelle note (sur 10) méritez-vous pour ces trois critères : 

#### Pertinence (0 étant insignifiant)

Note : 10

La version originale offre des résultats qui sont "intéressants" tandis qu'avec plusieurs espèces disponibles,
les résultats sont vraiment poussés à un autre niveau, que ce soit visuellement ou logiquement. Le fait d'avoir
un nombre varié d'espèces est la suite logique de la version à 2 états.

#### Difficulté (0 étant trivial)

Note : 6

Il est important de noté que la difficulté n'était pas vraiment dans l'aspect logique de l'ajout de plusieurs espèces,
mais plutôt dans le respect de la syntaxe moderne et professionnelle du C++ et de l'implémentation générale de celle-ci
ainsi que l'application des nouvelles notions apprises en classe (Classes, Algorithmes de manipulation de vecteurs, etc.). 

#### Qualité de l’implémentation (0 correspond à un travail dont vous ne parlerez pas en entrevu)

Note : 9

Le code a été écrit de façon modulaire et réutilisable pour facilité la lisibilité et la compréhension. De plus,
il a été construit afin de faciliter l'expansion futur de l'application.