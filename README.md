# Ray Tracing - LifProjet

![Capture d'écran](data/render0_0.jpg) <br>
Image d’une scène de notre application où l’on peut distinguer des sphères de différentes couleurs avec réflections sur les sphères et le sol.

### Presentation de l'agorithme de Ray-Tracing

Le Ray-Tracing est une technique permettant de générer une image en suivant le parcours de la lumière. <br>

Elle consiste à simuler le parcours inverse de la lumière : on calcule les éclairages de la caméra vers les objets puis vers les lumières, alors que dans la réalité la lumière va de la scène vers l'œil. <br>

Cette technique permet de produire des images de très haute qualité mais à un coût de calcul plus important que d’autre algorithme de calcul.<br>



### GROUPE
Constantin Magnin p1806593 <br>
Alban Saint-Sorny p1804792 <br>
Como Adrien       p1709079 <br>


### Utilite
----

Permettre d'executer du lancer de rayon, sur des scènes composées d'objet simple ou complexes (cube, plan et sphere) en prenant en compte reflection, refraction, transparence et couleurs.


### Installation et execution
----

Avoir un IDE utilisant CMakeList comme CLion et run à partir de l'IDE. <br>
Lorsque l'application est ouverte, choisir la scène, choisir le niveau de détails grâce au slider, puis appuyer sur le bouton render. <br>
Nous pouvons acceder à la DepthMap grace au bouton Shading et Toggle View.<br>


### Dependances
----

Ce code utilise QT : https://www.qt.io/download

### Autre captures
----
![Capture d'écran](data/img_1.jpg) <br>
![Capture d'écran](data/img_2.png) <br>
![Capture d'écran](data/img_3.png) <br>