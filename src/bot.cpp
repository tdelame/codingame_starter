# include "configuration.h"
# include "BitStream.h"
# include "CrashHandler.h"

// Interface to specialize for the game
struct CodinGameOutput { void finish() const noexcept { fprintf(stdout, "\n"); fflush(stdout);} };
struct LocalOutput { void finish() const noexcept {} };
struct Bot {
  virtual int loop() = 0;
  virtual void initialize(FILE* input, BitStream& bs, LocalOutput& output) = 0;
  virtual void step(FILE* input, BitStream& bs, LocalOutput& output) = 0;
  virtual void reload(BitStream& bs) = 0;
};

struct FirstBot: public Bot {
  int loop() override {
    CodinGameOutput output;
    BitStream bs;
    return 0;
  }

  void initialize(FILE* input, BitStream& bs, LocalOutput& output) override {}
  void step(FILE* input, BitStream& bs, LocalOutput& output) override {}
  void reload(BitStream& bs) override {}
};

int main() {
  fprintf(stderr, "[CRASH HANDLER] %s\n", CrashHandler::install() ? "initialized" : "NOT INITIALIZED");
  fprintf(stderr, "Bot is a %s version\n", is_codingame ? "CodinGame" : "Local");
  return FirstBot{}.loop();
}
