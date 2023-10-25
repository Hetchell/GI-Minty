#include "Discord.h"

void Discord::Initialize() {
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("1112360491847778344", &Handle, 1, NULL);
}

void Discord::Update() {
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "Hacking MHY <333";
    time_t CurrentTime = time(0);
    discordPresence.startTimestamp = CurrentTime;
    discordPresence.largeImageText = "https://linktr.ee/kindawindytoday";
    discordPresence.largeImageKey = "idol";
    discordPresence.smallImageKey = "gensh";
    discordPresence.smallImageText = "Genshin Impact";
    Discord_UpdatePresence(&discordPresence);
}
