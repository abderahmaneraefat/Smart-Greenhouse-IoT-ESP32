# Smart Greenhouse IoT System (ESP32)

Ce projet est un système intelligent pour le monitoring et l'automatisation d'une serre agricole. Il utilise l'ESP32, MQTT, Node-RED et le cloud ThingSpeak.

## Comment exécuter le projet

### 1. Matériel & Simulation (Wokwi)
1. Ouvrez Wokwi.
2. Créez un nouveau projet ESP32.
3. Copiez le contenu de sketch.ino dans l'onglet code.
4. Copiez le contenu de diagram.json dans l'onglet diagram.json pour configurer le circuit automatiquement.
5. Cliquez sur Play pour démarrer la simulation.

### 2. Communication (MQTT)
Le projet utilise le broker public HiveMQ (broker.hivemq.com). 
- L'ESP32 publie les données sur le topic : serre/data.
- Assurez-vous d'avoir une connexion internet pour que l'ESP32 puisse atteindre le broker.

### 3. Logique & Dashboard (Node-RED)
1. Lancez Node-RED localement.
2. Allez sur http://localhost:1880.
3. Cliquez sur Menu > Import et collez le contenu du fichier node_red_flow.json.
4. Cliquez sur Deploy.
5. Accédez à l'interface graphique sur : http://localhost:1880/ui.

### 4. Archivage Cloud (ThingSpeak)
1. Créez un compte sur ThingSpeak.
2. Créez un Channel avec quatre champs : Field 1 (Température), Field 2 (Humidité Air), Field 3 (Humidité Sol) et Field 4 (Luminosité).
3. Remplacez l'API Key dans le bloc de fonction de Node-RED par votre propre Write API Key.

## Fonctionnement du Système
* **Température > 30°C** : Le ventilateur (LED Rouge) s'allume automatiquement.
* **Sol Sec (Valeur > 2500)** : La pompe à eau (LED Bleue) s'active.
* **Faible Luminosité (Valeur > 2000)** : L'éclairage (LED Jaune) s'allume.
* **Température Critique (> 35°C)** : L'alarme (Buzzer + LED Orange) se déclenche.
* **Transmission des données** : Les informations sont envoyées au Dashboard et au Cloud par détection de changement.
