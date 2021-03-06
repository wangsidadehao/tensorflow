/* Copyright 2016 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Shim for systems that need to load both SessionBundle and
// SavedModelBundle interchangeably during migration to SavedModel.
#ifndef THIRD_PARTY_TENSORFLOW_CONTRIB_SESSION_BUNDLE_BUNDLE_SHIM_H_
#define THIRD_PARTY_TENSORFLOW_CONTRIB_SESSION_BUNDLE_BUNDLE_SHIM_H_

#include <memory>

#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/contrib/session_bundle/session_bundle.h"
#include "tensorflow/core/lib/core/status.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/public/session_options.h"

namespace tensorflow {
namespace serving {
namespace internal {

// Adds an entry (key and value) to the input map of the signature def.
void AddInputToSignatureDef(const string& tensor_name,
                            const string& input_map_key,
                            SignatureDef* signature_def);

// Adds an entry (key and value) to the output map of the signature def.
void AddOutputToSignatureDef(const string& tensor_name,
                             const string& output_map_key,
                             SignatureDef* signature_def);

// Converts signatures in the MetaGraphDef into a SignatureDefs in the
// MetaGraphDef.
Status ConvertSignaturesToSignatureDefs(MetaGraphDef* meta_graph_def);

// Converts a SessionBundle to a SavedModelBundle.
Status ConvertSessionBundleToSavedModelBundle(
    SessionBundle& session_bundle, SavedModelBundle* saved_model_bundle);

}  // namespace internal

// Loads a SavedModel from either a session-bundle path or a SavedModel bundle
// path.
Status LoadSessionBundleOrSavedModelBundle(
    const SessionOptions& session_options, const RunOptions& run_options,
    const string& export_dir, const std::unordered_set<string>& tags,
    SavedModelBundle* bundle);

// Checks whether the provided directory could contain a SessionBundle or a
// SavedModel. Note that the method does not load any data by itself. If the
// method returns `false`, the export directory definitely does not contain a
// SessionBundle or SavedModel. If the method returns `true`, the export
// directory may contain a SessionBundle or a SavedModel but provides no
// guarantee that it can be loaded.
bool MaybeSessionBundleOrSavedModelDirectory(const string& export_dir);

}  // namespace serving
}  // namespace tensorflow
#endif  // THIRD_PARTY_TENSORFLOW_CONTRIB_SESSION_BUNDLE_BUNDLE_SHIM_H_
