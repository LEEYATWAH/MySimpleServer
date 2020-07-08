// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: echoMessage.proto

#ifndef PROTOBUF_INCLUDED_echoMessage_2eproto
#define PROTOBUF_INCLUDED_echoMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_echoMessage_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_echoMessage_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_echoMessage_2eproto();
namespace qps_test {
class EchoMessage;
class EchoMessageDefaultTypeInternal;
extern EchoMessageDefaultTypeInternal _EchoMessage_default_instance_;
}  // namespace qps_test
namespace google {
namespace protobuf {
template<> ::qps_test::EchoMessage* Arena::CreateMaybeMessage<::qps_test::EchoMessage>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace qps_test {

// ===================================================================

class EchoMessage :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:qps_test.EchoMessage) */ {
 public:
  EchoMessage();
  virtual ~EchoMessage();

  EchoMessage(const EchoMessage& from);

  inline EchoMessage& operator=(const EchoMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  EchoMessage(EchoMessage&& from) noexcept
    : EchoMessage() {
    *this = ::std::move(from);
  }

  inline EchoMessage& operator=(EchoMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const EchoMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const EchoMessage* internal_default_instance() {
    return reinterpret_cast<const EchoMessage*>(
               &_EchoMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(EchoMessage* other);
  friend void swap(EchoMessage& a, EchoMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline EchoMessage* New() const final {
    return CreateMaybeMessage<EchoMessage>(nullptr);
  }

  EchoMessage* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<EchoMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const EchoMessage& from);
  void MergeFrom(const EchoMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(EchoMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string content = 1;
  void clear_content();
  static const int kContentFieldNumber = 1;
  const ::std::string& content() const;
  void set_content(const ::std::string& value);
  #if LANG_CXX11
  void set_content(::std::string&& value);
  #endif
  void set_content(const char* value);
  void set_content(const char* value, size_t size);
  ::std::string* mutable_content();
  ::std::string* release_content();
  void set_allocated_content(::std::string* content);

  // int32 id = 2;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:qps_test.EchoMessage)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr content_;
  ::google::protobuf::int32 id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_echoMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// EchoMessage

// string content = 1;
inline void EchoMessage::clear_content() {
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EchoMessage::content() const {
  // @@protoc_insertion_point(field_get:qps_test.EchoMessage.content)
  return content_.GetNoArena();
}
inline void EchoMessage::set_content(const ::std::string& value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qps_test.EchoMessage.content)
}
#if LANG_CXX11
inline void EchoMessage::set_content(::std::string&& value) {
  
  content_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qps_test.EchoMessage.content)
}
#endif
inline void EchoMessage::set_content(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qps_test.EchoMessage.content)
}
inline void EchoMessage::set_content(const char* value, size_t size) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qps_test.EchoMessage.content)
}
inline ::std::string* EchoMessage::mutable_content() {
  
  // @@protoc_insertion_point(field_mutable:qps_test.EchoMessage.content)
  return content_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EchoMessage::release_content() {
  // @@protoc_insertion_point(field_release:qps_test.EchoMessage.content)
  
  return content_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EchoMessage::set_allocated_content(::std::string* content) {
  if (content != nullptr) {
    
  } else {
    
  }
  content_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:qps_test.EchoMessage.content)
}

// int32 id = 2;
inline void EchoMessage::clear_id() {
  id_ = 0;
}
inline ::google::protobuf::int32 EchoMessage::id() const {
  // @@protoc_insertion_point(field_get:qps_test.EchoMessage.id)
  return id_;
}
inline void EchoMessage::set_id(::google::protobuf::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:qps_test.EchoMessage.id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace qps_test

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_echoMessage_2eproto