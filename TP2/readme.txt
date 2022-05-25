# TP2 d'Intelligence Artificielle pour le jeux vidéo #

Claire Saba - SABC14529902
Jehan Rouby - ROUJ06070007
Gabriel Roger - ROGG15040006


Pour ouvrir le programme, ouvrer avec Visual Studio la solution (nous avons utilisé Visual Studio 2019) :
"Buckland_Chapter3-Steering Behaviors\Steering.sln"
Appuyer sur le bouton "Débogueur Windows Local" pour lancer l'exécution.

L'exécutable du programme se trouve dans le dossier "Release".



# Fonctionnalités implémentées #

Comme demandé dans l'énoncé, nous avons d'abord implémenté une classe d'agent poursuiveur (Follower) qui utilise l'algorithme de poursuite en offset.
Nous avons ensuite implémenté une classe d'agent leader (Leader) qui se déplace en utilisant l'algorithme d'itinérance (Wandering).
Ces deux classes ont été instanciées dans un scénario basique où le leader est suivi par 20 poursuiveurs.

Nous avons ajouté un comportement contrôlé par un joueur pour l'agent leader. Celui-ci utilise l'algorithme Seek, et le joueur peut le contrôler via le clic gauche de la souris.
3 agents poursuiveurs entourent également le joueur humain. Nous n'étions cependant pas sûrs de ce qu'il fallait implémenter pour que ces 3 agents "protègent" le joueur des autres agents.

Enfin, nous avons amélioré le menu pour que celui-ci laisse la possibilité au joueur de choisir l'un des deux scénarios : agent leader qui se déplace aléatoirement, ou agent leader contrôlé à la souris.
Les couleurs des agents correspondent également à leur rôle : le leader est en rouge, les poursuiveurs qui protègent le leader sont en vert, et le reste des poursuiveurs sont en bleu.