/**************************************************************************/
/*                                                                        */
/*                          WWIV Version 5.x                              */
/*           Copyright (C)2016-2020, WWIV Software Services               */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/**************************************************************************/
#ifndef INCLUDED_NET_CORE_NET_CMDLINE_H
#define INCLUDED_NET_CORE_NET_CMDLINE_H

#include <chrono>
#include <memory>
#include <string>

#include "core/command_line.h"
#include <filesystem>
#include "sdk/config.h"
#include "sdk/net/net.h"
#include "sdk/net/networks.h"

namespace wwiv::net {

void AddStandardNetworkArgs(wwiv::core::CommandLine& cmdline);

/**
 * Wrapper class that augments CommandLine to specialize it for the network commands.
 */
class NetworkCommandLine {
public:
  NetworkCommandLine(wwiv::core::CommandLine& cmdline, char net_cmd);

  [[nodiscard]] bool IsInitialized() const noexcept { return initialized_; }
  [[nodiscard]] const wwiv::sdk::Config& config() const noexcept { return *config_; }
  [[nodiscard]] const wwiv::sdk::Networks& networks() const noexcept { return *networks_; }
  [[nodiscard]] std::string network_name() const noexcept { return network_name_; }
  [[nodiscard]] int network_number() const noexcept { return network_number_; }
  [[nodiscard]] const net_networks_rec& network() const noexcept { return network_; }
  [[nodiscard]] const wwiv::core::CommandLine& cmdline() const noexcept { return cmdline_; }
  [[nodiscard]] char net_cmd() const noexcept { return net_cmd_; }
  [[nodiscard]] std::filesystem::path semaphore_path() const noexcept;
  [[nodiscard]] std::string GetHelp() const;

  /** Process net.ini and reparse command line applying new defaults */
  [[nodiscard]] bool LoadNetIni(char net_cmd, const std::string& bbsdir);
  [[nodiscard]] bool skip_delete() const noexcept;
  [[nodiscard]] bool skip_net() const noexcept;
  [[nodiscard]] bool quiet() const noexcept;

  [[nodiscard]] std::chrono::duration<double> semaphore_timeout() const noexcept;

private:
  std::unique_ptr<wwiv::sdk::Config> config_;
  std::unique_ptr<wwiv::sdk::Networks> networks_;
  std::string network_name_;
  int network_number_{0};
  bool initialized_{true};
  net_networks_rec network_;
  wwiv::core::CommandLine& cmdline_;
  char net_cmd_;
};

} // namespace wwiv::net

#endif // INCLUDED_NET_CORE_NET_CMDLINE_H
