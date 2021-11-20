// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: order.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_order_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_order_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/any.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_order_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_order_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_order_2eproto;
namespace exchange {
class CancelOrder;
struct CancelOrderDefaultTypeInternal;
extern CancelOrderDefaultTypeInternal _CancelOrder_default_instance_;
class FlushOrderBook;
struct FlushOrderBookDefaultTypeInternal;
extern FlushOrderBookDefaultTypeInternal _FlushOrderBook_default_instance_;
class Message;
struct MessageDefaultTypeInternal;
extern MessageDefaultTypeInternal _Message_default_instance_;
class NewOrder;
struct NewOrderDefaultTypeInternal;
extern NewOrderDefaultTypeInternal _NewOrder_default_instance_;
}  // namespace exchange
PROTOBUF_NAMESPACE_OPEN
template<> ::exchange::CancelOrder* Arena::CreateMaybeMessage<::exchange::CancelOrder>(Arena*);
template<> ::exchange::FlushOrderBook* Arena::CreateMaybeMessage<::exchange::FlushOrderBook>(Arena*);
template<> ::exchange::Message* Arena::CreateMaybeMessage<::exchange::Message>(Arena*);
template<> ::exchange::NewOrder* Arena::CreateMaybeMessage<::exchange::NewOrder>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace exchange {

enum NewOrder_SideType : int {
  NewOrder_SideType_BUY = 0,
  NewOrder_SideType_SELL = 1,
  NewOrder_SideType_NewOrder_SideType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  NewOrder_SideType_NewOrder_SideType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool NewOrder_SideType_IsValid(int value);
constexpr NewOrder_SideType NewOrder_SideType_SideType_MIN = NewOrder_SideType_BUY;
constexpr NewOrder_SideType NewOrder_SideType_SideType_MAX = NewOrder_SideType_SELL;
constexpr int NewOrder_SideType_SideType_ARRAYSIZE = NewOrder_SideType_SideType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* NewOrder_SideType_descriptor();
template<typename T>
inline const std::string& NewOrder_SideType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, NewOrder_SideType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function NewOrder_SideType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    NewOrder_SideType_descriptor(), enum_t_value);
}
inline bool NewOrder_SideType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, NewOrder_SideType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<NewOrder_SideType>(
    NewOrder_SideType_descriptor(), name, value);
}
// ===================================================================

class NewOrder final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:exchange.NewOrder) */ {
 public:
  inline NewOrder() : NewOrder(nullptr) {}
  ~NewOrder() override;
  explicit constexpr NewOrder(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  NewOrder(const NewOrder& from);
  NewOrder(NewOrder&& from) noexcept
    : NewOrder() {
    *this = ::std::move(from);
  }

  inline NewOrder& operator=(const NewOrder& from) {
    CopyFrom(from);
    return *this;
  }
  inline NewOrder& operator=(NewOrder&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const NewOrder& default_instance() {
    return *internal_default_instance();
  }
  static inline const NewOrder* internal_default_instance() {
    return reinterpret_cast<const NewOrder*>(
               &_NewOrder_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(NewOrder& a, NewOrder& b) {
    a.Swap(&b);
  }
  inline void Swap(NewOrder* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(NewOrder* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline NewOrder* New() const final {
    return new NewOrder();
  }

  NewOrder* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<NewOrder>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const NewOrder& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const NewOrder& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NewOrder* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "exchange.NewOrder";
  }
  protected:
  explicit NewOrder(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef NewOrder_SideType SideType;
  static constexpr SideType BUY =
    NewOrder_SideType_BUY;
  static constexpr SideType SELL =
    NewOrder_SideType_SELL;
  static inline bool SideType_IsValid(int value) {
    return NewOrder_SideType_IsValid(value);
  }
  static constexpr SideType SideType_MIN =
    NewOrder_SideType_SideType_MIN;
  static constexpr SideType SideType_MAX =
    NewOrder_SideType_SideType_MAX;
  static constexpr int SideType_ARRAYSIZE =
    NewOrder_SideType_SideType_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  SideType_descriptor() {
    return NewOrder_SideType_descriptor();
  }
  template<typename T>
  static inline const std::string& SideType_Name(T enum_t_value) {
    static_assert(::std::is_same<T, SideType>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function SideType_Name.");
    return NewOrder_SideType_Name(enum_t_value);
  }
  static inline bool SideType_Parse(::PROTOBUF_NAMESPACE_ID::ConstStringParam name,
      SideType* value) {
    return NewOrder_SideType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kSymbolFieldNumber = 2,
    kUserFieldNumber = 1,
    kPriceFieldNumber = 3,
    kQuantityFieldNumber = 4,
    kSideFieldNumber = 5,
    kUserOrderFieldNumber = 6,
  };
  // string symbol = 2;
  void clear_symbol();
  const std::string& symbol() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_symbol(ArgT0&& arg0, ArgT... args);
  std::string* mutable_symbol();
  PROTOBUF_MUST_USE_RESULT std::string* release_symbol();
  void set_allocated_symbol(std::string* symbol);
  private:
  const std::string& _internal_symbol() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_symbol(const std::string& value);
  std::string* _internal_mutable_symbol();
  public:

  // uint32 user = 1;
  void clear_user();
  ::PROTOBUF_NAMESPACE_ID::uint32 user() const;
  void set_user(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_user() const;
  void _internal_set_user(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 price = 3;
  void clear_price();
  ::PROTOBUF_NAMESPACE_ID::uint32 price() const;
  void set_price(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_price() const;
  void _internal_set_price(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 quantity = 4;
  void clear_quantity();
  ::PROTOBUF_NAMESPACE_ID::uint32 quantity() const;
  void set_quantity(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_quantity() const;
  void _internal_set_quantity(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // .exchange.NewOrder.SideType side = 5;
  void clear_side();
  ::exchange::NewOrder_SideType side() const;
  void set_side(::exchange::NewOrder_SideType value);
  private:
  ::exchange::NewOrder_SideType _internal_side() const;
  void _internal_set_side(::exchange::NewOrder_SideType value);
  public:

  // uint32 userOrder = 6;
  void clear_userorder();
  ::PROTOBUF_NAMESPACE_ID::uint32 userorder() const;
  void set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_userorder() const;
  void _internal_set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:exchange.NewOrder)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr symbol_;
  ::PROTOBUF_NAMESPACE_ID::uint32 user_;
  ::PROTOBUF_NAMESPACE_ID::uint32 price_;
  ::PROTOBUF_NAMESPACE_ID::uint32 quantity_;
  int side_;
  ::PROTOBUF_NAMESPACE_ID::uint32 userorder_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_order_2eproto;
};
// -------------------------------------------------------------------

class CancelOrder final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:exchange.CancelOrder) */ {
 public:
  inline CancelOrder() : CancelOrder(nullptr) {}
  ~CancelOrder() override;
  explicit constexpr CancelOrder(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CancelOrder(const CancelOrder& from);
  CancelOrder(CancelOrder&& from) noexcept
    : CancelOrder() {
    *this = ::std::move(from);
  }

  inline CancelOrder& operator=(const CancelOrder& from) {
    CopyFrom(from);
    return *this;
  }
  inline CancelOrder& operator=(CancelOrder&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CancelOrder& default_instance() {
    return *internal_default_instance();
  }
  static inline const CancelOrder* internal_default_instance() {
    return reinterpret_cast<const CancelOrder*>(
               &_CancelOrder_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(CancelOrder& a, CancelOrder& b) {
    a.Swap(&b);
  }
  inline void Swap(CancelOrder* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CancelOrder* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline CancelOrder* New() const final {
    return new CancelOrder();
  }

  CancelOrder* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CancelOrder>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CancelOrder& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const CancelOrder& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CancelOrder* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "exchange.CancelOrder";
  }
  protected:
  explicit CancelOrder(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserFieldNumber = 1,
    kUserOrderFieldNumber = 2,
  };
  // uint32 user = 1;
  void clear_user();
  ::PROTOBUF_NAMESPACE_ID::uint32 user() const;
  void set_user(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_user() const;
  void _internal_set_user(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 userOrder = 2;
  void clear_userorder();
  ::PROTOBUF_NAMESPACE_ID::uint32 userorder() const;
  void set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_userorder() const;
  void _internal_set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:exchange.CancelOrder)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 user_;
  ::PROTOBUF_NAMESPACE_ID::uint32 userorder_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_order_2eproto;
};
// -------------------------------------------------------------------

class FlushOrderBook final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:exchange.FlushOrderBook) */ {
 public:
  inline FlushOrderBook() : FlushOrderBook(nullptr) {}
  ~FlushOrderBook() override;
  explicit constexpr FlushOrderBook(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  FlushOrderBook(const FlushOrderBook& from);
  FlushOrderBook(FlushOrderBook&& from) noexcept
    : FlushOrderBook() {
    *this = ::std::move(from);
  }

  inline FlushOrderBook& operator=(const FlushOrderBook& from) {
    CopyFrom(from);
    return *this;
  }
  inline FlushOrderBook& operator=(FlushOrderBook&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const FlushOrderBook& default_instance() {
    return *internal_default_instance();
  }
  static inline const FlushOrderBook* internal_default_instance() {
    return reinterpret_cast<const FlushOrderBook*>(
               &_FlushOrderBook_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(FlushOrderBook& a, FlushOrderBook& b) {
    a.Swap(&b);
  }
  inline void Swap(FlushOrderBook* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(FlushOrderBook* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline FlushOrderBook* New() const final {
    return new FlushOrderBook();
  }

  FlushOrderBook* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<FlushOrderBook>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const FlushOrderBook& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const FlushOrderBook& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FlushOrderBook* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "exchange.FlushOrderBook";
  }
  protected:
  explicit FlushOrderBook(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:exchange.FlushOrderBook)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_order_2eproto;
};
// -------------------------------------------------------------------

class Message final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:exchange.Message) */ {
 public:
  inline Message() : Message(nullptr) {}
  ~Message() override;
  explicit constexpr Message(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Message(const Message& from);
  Message(Message&& from) noexcept
    : Message() {
    *this = ::std::move(from);
  }

  inline Message& operator=(const Message& from) {
    CopyFrom(from);
    return *this;
  }
  inline Message& operator=(Message&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Message& default_instance() {
    return *internal_default_instance();
  }
  static inline const Message* internal_default_instance() {
    return reinterpret_cast<const Message*>(
               &_Message_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(Message& a, Message& b) {
    a.Swap(&b);
  }
  inline void Swap(Message* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Message* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Message* New() const final {
    return new Message();
  }

  Message* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Message>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Message& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Message& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Message* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "exchange.Message";
  }
  protected:
  explicit Message(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCommandFieldNumber = 2,
    kSequenceNumberFieldNumber = 1,
  };
  // .google.protobuf.Any command = 2;
  bool has_command() const;
  private:
  bool _internal_has_command() const;
  public:
  void clear_command();
  const PROTOBUF_NAMESPACE_ID::Any& command() const;
  PROTOBUF_MUST_USE_RESULT PROTOBUF_NAMESPACE_ID::Any* release_command();
  PROTOBUF_NAMESPACE_ID::Any* mutable_command();
  void set_allocated_command(PROTOBUF_NAMESPACE_ID::Any* command);
  private:
  const PROTOBUF_NAMESPACE_ID::Any& _internal_command() const;
  PROTOBUF_NAMESPACE_ID::Any* _internal_mutable_command();
  public:
  void unsafe_arena_set_allocated_command(
      PROTOBUF_NAMESPACE_ID::Any* command);
  PROTOBUF_NAMESPACE_ID::Any* unsafe_arena_release_command();

  // uint64 sequenceNumber = 1;
  void clear_sequencenumber();
  ::PROTOBUF_NAMESPACE_ID::uint64 sequencenumber() const;
  void set_sequencenumber(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_sequencenumber() const;
  void _internal_set_sequencenumber(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // @@protoc_insertion_point(class_scope:exchange.Message)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  PROTOBUF_NAMESPACE_ID::Any* command_;
  ::PROTOBUF_NAMESPACE_ID::uint64 sequencenumber_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_order_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NewOrder

// uint32 user = 1;
inline void NewOrder::clear_user() {
  user_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::_internal_user() const {
  return user_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::user() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.user)
  return _internal_user();
}
inline void NewOrder::_internal_set_user(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  user_ = value;
}
inline void NewOrder::set_user(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_user(value);
  // @@protoc_insertion_point(field_set:exchange.NewOrder.user)
}

// string symbol = 2;
inline void NewOrder::clear_symbol() {
  symbol_.ClearToEmpty();
}
inline const std::string& NewOrder::symbol() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.symbol)
  return _internal_symbol();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void NewOrder::set_symbol(ArgT0&& arg0, ArgT... args) {
 
 symbol_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:exchange.NewOrder.symbol)
}
inline std::string* NewOrder::mutable_symbol() {
  std::string* _s = _internal_mutable_symbol();
  // @@protoc_insertion_point(field_mutable:exchange.NewOrder.symbol)
  return _s;
}
inline const std::string& NewOrder::_internal_symbol() const {
  return symbol_.Get();
}
inline void NewOrder::_internal_set_symbol(const std::string& value) {
  
  symbol_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* NewOrder::_internal_mutable_symbol() {
  
  return symbol_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* NewOrder::release_symbol() {
  // @@protoc_insertion_point(field_release:exchange.NewOrder.symbol)
  return symbol_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void NewOrder::set_allocated_symbol(std::string* symbol) {
  if (symbol != nullptr) {
    
  } else {
    
  }
  symbol_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), symbol,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:exchange.NewOrder.symbol)
}

// uint32 price = 3;
inline void NewOrder::clear_price() {
  price_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::_internal_price() const {
  return price_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::price() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.price)
  return _internal_price();
}
inline void NewOrder::_internal_set_price(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  price_ = value;
}
inline void NewOrder::set_price(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_price(value);
  // @@protoc_insertion_point(field_set:exchange.NewOrder.price)
}

// uint32 quantity = 4;
inline void NewOrder::clear_quantity() {
  quantity_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::_internal_quantity() const {
  return quantity_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::quantity() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.quantity)
  return _internal_quantity();
}
inline void NewOrder::_internal_set_quantity(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  quantity_ = value;
}
inline void NewOrder::set_quantity(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_quantity(value);
  // @@protoc_insertion_point(field_set:exchange.NewOrder.quantity)
}

// .exchange.NewOrder.SideType side = 5;
inline void NewOrder::clear_side() {
  side_ = 0;
}
inline ::exchange::NewOrder_SideType NewOrder::_internal_side() const {
  return static_cast< ::exchange::NewOrder_SideType >(side_);
}
inline ::exchange::NewOrder_SideType NewOrder::side() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.side)
  return _internal_side();
}
inline void NewOrder::_internal_set_side(::exchange::NewOrder_SideType value) {
  
  side_ = value;
}
inline void NewOrder::set_side(::exchange::NewOrder_SideType value) {
  _internal_set_side(value);
  // @@protoc_insertion_point(field_set:exchange.NewOrder.side)
}

// uint32 userOrder = 6;
inline void NewOrder::clear_userorder() {
  userorder_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::_internal_userorder() const {
  return userorder_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 NewOrder::userorder() const {
  // @@protoc_insertion_point(field_get:exchange.NewOrder.userOrder)
  return _internal_userorder();
}
inline void NewOrder::_internal_set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  userorder_ = value;
}
inline void NewOrder::set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_userorder(value);
  // @@protoc_insertion_point(field_set:exchange.NewOrder.userOrder)
}

// -------------------------------------------------------------------

// CancelOrder

// uint32 user = 1;
inline void CancelOrder::clear_user() {
  user_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CancelOrder::_internal_user() const {
  return user_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CancelOrder::user() const {
  // @@protoc_insertion_point(field_get:exchange.CancelOrder.user)
  return _internal_user();
}
inline void CancelOrder::_internal_set_user(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  user_ = value;
}
inline void CancelOrder::set_user(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_user(value);
  // @@protoc_insertion_point(field_set:exchange.CancelOrder.user)
}

// uint32 userOrder = 2;
inline void CancelOrder::clear_userorder() {
  userorder_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CancelOrder::_internal_userorder() const {
  return userorder_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CancelOrder::userorder() const {
  // @@protoc_insertion_point(field_get:exchange.CancelOrder.userOrder)
  return _internal_userorder();
}
inline void CancelOrder::_internal_set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  userorder_ = value;
}
inline void CancelOrder::set_userorder(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_userorder(value);
  // @@protoc_insertion_point(field_set:exchange.CancelOrder.userOrder)
}

// -------------------------------------------------------------------

// FlushOrderBook

// -------------------------------------------------------------------

// Message

// uint64 sequenceNumber = 1;
inline void Message::clear_sequencenumber() {
  sequencenumber_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Message::_internal_sequencenumber() const {
  return sequencenumber_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Message::sequencenumber() const {
  // @@protoc_insertion_point(field_get:exchange.Message.sequenceNumber)
  return _internal_sequencenumber();
}
inline void Message::_internal_set_sequencenumber(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  sequencenumber_ = value;
}
inline void Message::set_sequencenumber(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_sequencenumber(value);
  // @@protoc_insertion_point(field_set:exchange.Message.sequenceNumber)
}

// .google.protobuf.Any command = 2;
inline bool Message::_internal_has_command() const {
  return this != internal_default_instance() && command_ != nullptr;
}
inline bool Message::has_command() const {
  return _internal_has_command();
}
inline const PROTOBUF_NAMESPACE_ID::Any& Message::_internal_command() const {
  const PROTOBUF_NAMESPACE_ID::Any* p = command_;
  return p != nullptr ? *p : reinterpret_cast<const PROTOBUF_NAMESPACE_ID::Any&>(
      PROTOBUF_NAMESPACE_ID::_Any_default_instance_);
}
inline const PROTOBUF_NAMESPACE_ID::Any& Message::command() const {
  // @@protoc_insertion_point(field_get:exchange.Message.command)
  return _internal_command();
}
inline void Message::unsafe_arena_set_allocated_command(
    PROTOBUF_NAMESPACE_ID::Any* command) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(command_);
  }
  command_ = command;
  if (command) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:exchange.Message.command)
}
inline PROTOBUF_NAMESPACE_ID::Any* Message::release_command() {
  
  PROTOBUF_NAMESPACE_ID::Any* temp = command_;
  command_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline PROTOBUF_NAMESPACE_ID::Any* Message::unsafe_arena_release_command() {
  // @@protoc_insertion_point(field_release:exchange.Message.command)
  
  PROTOBUF_NAMESPACE_ID::Any* temp = command_;
  command_ = nullptr;
  return temp;
}
inline PROTOBUF_NAMESPACE_ID::Any* Message::_internal_mutable_command() {
  
  if (command_ == nullptr) {
    auto* p = CreateMaybeMessage<PROTOBUF_NAMESPACE_ID::Any>(GetArenaForAllocation());
    command_ = p;
  }
  return command_;
}
inline PROTOBUF_NAMESPACE_ID::Any* Message::mutable_command() {
  PROTOBUF_NAMESPACE_ID::Any* _msg = _internal_mutable_command();
  // @@protoc_insertion_point(field_mutable:exchange.Message.command)
  return _msg;
}
inline void Message::set_allocated_command(PROTOBUF_NAMESPACE_ID::Any* command) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(command_);
  }
  if (command) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(command));
    if (message_arena != submessage_arena) {
      command = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, command, submessage_arena);
    }
    
  } else {
    
  }
  command_ = command;
  // @@protoc_insertion_point(field_set_allocated:exchange.Message.command)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace exchange

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::exchange::NewOrder_SideType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::exchange::NewOrder_SideType>() {
  return ::exchange::NewOrder_SideType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_order_2eproto
