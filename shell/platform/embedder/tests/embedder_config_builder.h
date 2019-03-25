// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_
#define FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_

#include "flutter/fml/macros.h"
#include "flutter/fml/unique_object.h"
#include "flutter/shell/platform/embedder/embedder.h"
#include "flutter/shell/platform/embedder/tests/embedder_test.h"

namespace shell {
namespace testing {

struct UniqueEngineTraits {
  static FlutterEngine InvalidValue() { return nullptr; }

  static bool IsValid(const FlutterEngine& value) { return value != nullptr; }

  static void Free(FlutterEngine engine) {
    auto result = FlutterEngineShutdown(engine);
    FML_CHECK(result == kSuccess);
  }
};

using UniqueEngine = fml::UniqueObject<FlutterEngine, UniqueEngineTraits>;

class EmbedderConfigBuilder {
 public:
  EmbedderConfigBuilder();

  ~EmbedderConfigBuilder();

  void SetSoftwareRendererConfig();

  void SetAssetsPathFromFixture(const EmbedderTest* fixture);

  void SetSnapshotsFromFixture(const EmbedderTest* fixture);

  UniqueEngine LaunchEngine(void* user_data = nullptr) const;

 private:
  FlutterProjectArgs project_args_ = {};
  FlutterRendererConfig renderer_config_ = {};
  FlutterSoftwareRendererConfig software_renderer_config_ = {};
  std::string assets_path_;

  FML_DISALLOW_COPY_AND_ASSIGN(EmbedderConfigBuilder);
};

}  // namespace testing
}  // namespace shell

#endif  // FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_
