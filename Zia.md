Le serveur Zia s’organise autour d’un Pipe a travers lequel, la transaction recontrera differents module qui effectuerons les actions necessaire dans le but de fournir la reponse adequat. Par example, prenons une requete Http classique visant a executer un script PHP. L’url en question est ‘http://127.0.0.1/index.php’. La configuration du serveur se presente comme cela:

```javascript
{
  "conf": {
    "http": {
      "rules": {
        "port": 80
      },
    },
    "gzip": {
      "name": "gzip",
      "rules": {
        "http": {
          "Accept-Encoding": ["gzip"]
        }
      }
    }
  }
  "servers": {
    "google.fr": {
      "ip": "127.0.0.1:80",
      "directory": "/var/www",
      "conf": {
        "http": {
          "auth": {
            "/var/www/admin": {
              "admin": "admin"
            }
          }
        }
      },
      "modules": [ // ALL
        { // FIRST
        "http": {
          "modules": [ // ALL
            "gzip", // Module
            {
              // Modiule
              "name": "log",
              "file": "access.log"
            },
            { // FIRST
              "static": { // Module
                "file": "index.html",
                "rules": {
                  "http": {
                    "url": ["/", "/about", "/toto"]
                  }
                },
              },
              "php": { // Module
                "rules": {
                  "http": {
                    "url": ["*.php"]
                  }
                }
              },
              "python": { // Module
                "rules": ["url": ["*.py"]]
              },
              "file": {}, // Module
              "directory": {} // Module
            }
          ]
        },
        "ftp": { // Module
          "rules": {
            "port": [21]
          },
          "auth": { // Module
            "/var/www/admin": {
              "admin": "admin"
            }
          }
        }
      }]
    },
    "google.com": {}
  }
}
```

Pour l'example, celle-ci est au format JSON. Tout d'abord, l'element
`conf` de l'object situe a la racine permet de definir une configuration
globale des modules. Par la suite, lors de la definitions de la
hierarchie des module, les configurations renseignees heriterons de
celle-ci.

Le second element `servers` permet de definir les differents serveurs
virtuels interpretes par le Zia. Le nommmage des ces different serveur
ne peut s'effectuer uniquement en fonction:
  - Du port d'entre concerne
  - De l'ip du serveur
  - De l'ip du client
Il ne peut en aucun cas se baser reelement sur le champ `host` de la
requete Http car cela implique que la requete Http a deja ete parsee.
Or, dans le cas present, le parser Http est un module au meme titre que
les autres.
Le premier serveur nome `google.fr` reseigne tout d'abord la
configuration de l'hote virtuel:
  - l'adresse ip du serveur concerne. Ici 127.0.0.1.
  - le port d'ecoute concerne. Ici, 80.
  - la racine dans le systeme de fichier du serveur (purement indicatif
pour les modules intervenant)

L'element `conf` fait ici lieu de seconde couche d'heritage sur la
configurations de modules intervenants.
L'element `modules` determine les module intervenants pour un requete
effectue sur cet hote. Des lors, un tableau (`[]`) indique que chaque
module du tableau passera la requete au premier suivant respectant ses
conditions. Un objet (`{}`) indique que le premier module respectant ses
conditions traitera la transaction sans passer par les autres.

La semantique attendu est la suivante. Conciderant le module nome
`file`. Si celui ci est contenu dans un tableau, il doit etre represente
par un objet de telle sorte que celui-ci contienne un attribut `name`
correspondant au nom du module:

```javascript
[
  {
    "name": "file"
  }
]

```
C'est par ailleur la seule maniere de disintinguer un module d'un liste
de module.

Dans un objet, le module doit etre renseigner par un element le la liste
object  nomme de la meme maniere que le module:

```javascript
{
  "file": {

  }
}

```

Un module ne peut donc pas se nommer `name`. C'est en effet la seule
maniere de distinguer un module d'une liste `FIRST`.

Des lors, le serveur peut entammer le traitment de la transaction.
Il va donc chercher a savoir si le premier module de sa liste est
capable de traiter la demande. Ici, la requete s'effectue sur le port
80. Comme defini, le module `http` pose comme unique condition que la
requete s'effectue sur le port 80. Il respecte donc toute ses condition
et va donc pouvoir traiter la requete. Comme le module `http` fait
partie d'une liste `FIRST` (un objet), les modules suivant ne seront pas
interroge et le module `http` sera le seul appele a ce niveau.

## Comportement d'un module

Le module `http` va donc pouvoir entamer le traitement. Il recevera un
objet `Transaction` qui contiendra notaement le handler du socket a
travers lequel s'effectue la transaction, une liste de `Module`.
L'objet `Module` reseigne la configuation des modules en lecture seule
et une map accessible en lecture par les module non proprietaire et en
ecriture par le module proprietaire.
Un module ne peut acceder uniquement a la map des modules intervenant
avant lui meme.

Par la suite, le module `http` appellera tout ses modules fils
respectant toute leurs conditions car la liste de ses fils est une liste
`ALL` (un tableau `[]`). Le premier d'entre eux est le module `gzip`. Sa
configuration (definie plus haut) stipule que le module `http` doit
avoir reconnu le header `Accept-Encoding` comme contenant `gzip` pour
celui-ci intervienne. Si tel est le cas, le prochain module a traiter la
transaction sera le module `gzip`. Autrement, il sera ignore. Le
prochaine module `log` n'impose aucune condition particuliaire, il sera
donc appelle. Suite a quoi nous avons un objet. Celui-ci ne comporte pas
d'element `name` c'est donc une liste `FIRST` et nom pas un module. Le
premier module respectant toute ses condition prendra donc la main. Dans
le cas present, le premier est le module `static`. Celui-ci impose que
l'url (determine par le module `http`) soit soit '/', '/about' ou
'/toto'. Ce n'est pas le cas ici. Le prochain module est le module
`php`. La seule condition impose par ce module est que l'url se termine
par `.php`. Cette condition est respecte et le module `php` va donc
prendre la main. Les modules `python`, `file` et `directory` ne seront
pas verifier etant donne que nous sommes dans un liste `FIRST`.

Le module `php` n'ayant aucun module fils, nous connaissons donc tout
les modules intervenant dans la presente transaction. Considerons que le
client accepte la compression gzip et la liste est la suivante:

http -> gzip -> log -> php

Notez ici que le module gizip n'interient pas encore si la requete n'ext
pas compresse.

Des lors que le module `php` commencera a renvoyer sa reponse, le
processus inverse se ferra. La reponse passera par le module `log` puis
par le module `gzip` et enfin par le module `http` qui se chargera de
construitre l'entete de la reponse.



Afin d'optimiser l'utilisation du CPU du serveur, nous faisons le choix
de mettre une place une event loop plutot que ce dedier un processus a
chaque requete. Chaque event loop sera donc ratacher a un seul thread et
pourra gerer plusiseurs requete simultanement. Une seule instance de
chaque module exsistera par event loop et chacun evoluera dans son
propre thread pour des question de securite en cas de crash d'un des
modules.
Un objet `ModuleManager` sera charge de gere les module. Celui-ci
abstraira l'objet `EventLoop` et se propesera en factory d'objet
`Module` qui seront eux meme des abstration d'objet `Evented` capable
d'evoluer dans une `EventLoop`.
Le role de l'`EventLoop` est donc d'ordonner les objet `Evented` qu'elle
contient. Les objets `Evented` possederonts des methode telle que `on`,
`once`, `trigger` permettant de recevoir et de lever des evenement gere
par l'`EventLoop`.
Le `ModuleManager` sera quant a lui responssable de gerer le changement
de context des module en passant de module en module des objets
`Transaction` abstrayant eux memes des `CrossModulePackage`. Ces objets
`Transaction` contiendront sur les informations sur l'hote ainsi que
les configurations des differents modules intervenant dans la
transaction et les context cree par les differents modules precedents.
