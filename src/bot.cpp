# include "BotInterface.h"
# include "CrashHandler.h"

struct FirstBot: public BotInterface {
  FirstBot(const BotInitializer& initializer) : BotInterface(initializer){}

  int loop() override {
    BotController controller{stdin};
    Output output;
    BitStream bs;
    BitStream* bspointer = with_state_output ? &bs : nullptr;

    try {
      initialize(controller, output, bspointer);
      while (true) {
        step(controller, output, bspointer);
      }
    }
    catch (const std::exception& exc) {
      fprintf(stderr, "[CRASH] unhandled exception '%s'", exc.what());
      return 1;
    }
    return 0;
  }

  void initialize(BotController& controller, Output& output, BitStream* bs) override {
    (void)controller;
    (void)output;
    (void)bs;
  }
  void step(BotController& controller, Output& output, BitStream* bs) override {
    (void)controller;
    (void)output;
    (void)bs;
  }
  void reload(BitStream& bs) override {
    (void)bs;
  }
};
REGISTER_BOT(FirstBot);

int main() {
  fprintf(stderr, "[CRASH HANDLER] %s\n", INSTALL_CRASH_HANDLER ? "initialized" : "NOT INITIALIZED");
  fprintf(stderr, "Bot is a %s version\n", is_codingame ? "CodinGame" : "Local");
  return FirstBot{BotInitializer{}}.loop();
}
