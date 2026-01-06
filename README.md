# 🌿 Smart Greenhouse IoT System (ESP32)

Ce projet est un système intelligent pour le monitoring et l'automatisation d'une serre agricole. Il utilise l'**ESP32**, **MQTT**, **Node-RED** et le cloud **ThingSpeak**.

## 🚀 Comment exécuter le projet

### 1. Matériel & Simulation (Wokwi)
1. Ouvrez [Wokwi](https://wokwi.com).
2. Créez un nouveau projet **ESP32**.
3. Copiez le contenu de `serre_iot.ino` dans l'onglet code.
4. Copiez le contenu de `diagram.json` dans l'onglet `diagram.json` pour configurer le circuit automatiquement.
5. Cliquez sur **Play** pour démarrer la simulation.

### 2. Communication (MQTT)
Le projet utilise le broker public HiveMQ (`broker.hivemq.com`). 
- L'ESP32 publie les données sur le topic : `ma_serre/data`.
- Assurez-vous d'avoir une connexion internet pour que l'ESP32 puisse atteindre le broker.

### 3. Logique & Dashboard (Node-RED)
1. Lancez Node-RED localement en tapant `node-red` dans votre terminal.
2. Allez sur `http://localhost:1880`.
3. Cliquez sur **Menu > Import** et collez le contenu du fichier `node_red_flow.json`.
4. Cliquez sur **Deploy**.
5. Accédez à l'interface graphique sur : `http://localhost:1880/ui`.

### 4. Archivage Cloud (ThingSpeak)
1. Créez un compte sur [ThingSpeak](https://thingspeak.com).
2. Créez un Channel avec deux champs : `Field 1` (Température) et `Field 2` (Humidité).
3. Remplacez l'API Key dans les blocs **http request** de Node-RED par votre propre **Write API Key**.

## 📊 Fonctionnement du Système
- **Température > 30°C** : Le ventilateur (LED Rouge) s'allume automatiquement.
- **Humidité < 40%** : La pompe à eau (LED Bleue) s'active.
- Les données sont envoyées toutes les 5 secondes vers le Dashboard et le Cloud.

---
**Auteur :** Abderahmane Raefat  
**Lien du Projet :** [https://github.com/abderahmaneraefat/Smart-Greenhouse-IoT-ESP32](https://github.com/abderahmaneraefat/Smart-Greenhouse-IoT-ESP32)
