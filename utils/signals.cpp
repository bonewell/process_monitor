#include "signals.h"

#include <csignal>

namespace utils {

Signals::Signals()
    : Signals{ SIGINT, SIGTERM, SIGQUIT } {
}

Signals::Signals(std::initializer_list<int> signals)
    : signals_ { signals } {
  Unsubscribe();
}

int Signals::Wait() {
  sigset_t waitset;
  sigemptyset(&waitset);
  for (const auto& s: signals_) {
    sigaddset(&waitset, s);
  }
  int sig;
  return sigwait(&waitset, &sig);
}

void Signals::Unsubscribe() {
  sigset_t signal_set;
  sigemptyset(&signal_set);
  for (const auto& s: signals_) {
    sigaddset(&signal_set, s);
  }
  pthread_sigmask(SIG_BLOCK, &signal_set, nullptr);
}

}  // namespace utils
