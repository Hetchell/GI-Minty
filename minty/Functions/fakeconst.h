#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../HookManager.h"

template<class ...TParams>
class TEvent : public IEvent<TParams...>
{
    using TMyEventHandlerPtr = typename TypeHelper<TParams...>::TEventHandlerPtr;
    using TMyEventHandlerIt = typename TypeHelper<TParams...>::TEventHandlerIt;
    using TMyHandlerRunner = HandlerRunner<TParams...>;

public:

    TEvent() :
        m_core()
    {
    }

    TEvent(const TEvent& other) : m_core(other.m_core), m_handlerRunners(other.m_handlerRunners)
    {

    }

    virtual void operator()(TParams... params)
    {
        TMyHandlerRunner newHandlerRunner(m_core);

        m_core.coreMutex.lock_shared();
        auto it = m_handlerRunners.insert(m_handlerRunners.end(), &newHandlerRunner);
        m_core.coreMutex.unlock_shared();

        newHandlerRunner.run(params...);

        m_core.coreMutex.lock_shared();
        m_handlerRunners.erase(it);
        m_core.coreMutex.unlock_shared();
    }

protected:

    virtual bool isHandlerAdded(const TMyEventHandlerPtr& eventHandler) const override
    {
        std::shared_lock<std::shared_mutex> _coreMutexLock(m_core.coreMutex);

        return (findEventHandler(eventHandler) != m_core.handlers.end());

    }
    virtual bool addHandler(TMyEventHandlerPtr eventHandler) override
    {
        std::unique_lock<std::shared_mutex> _coreMutexLock(m_core.coreMutex);

        if (findEventHandler(eventHandler) == m_core.handlers.end())
        {
            m_core.handlers.push_back(std::move(eventHandler));
            return true;
        }
        return false;
    }
    virtual bool removeHandler(TMyEventHandlerPtr eventHandler) override
    {
        std::unique_lock<std::shared_mutex> _coreMutexLock(m_core.coreMutex);

        auto it = findEventHandler(eventHandler);
        if (it != m_core.handlers.end())
        {
            for (TMyHandlerRunner* oneHandlerRunner : m_handlerRunners)
            {
                if (it == oneHandlerRunner->currentIt)
                {
                    ++oneHandlerRunner->currentIt;
                    oneHandlerRunner->wasRemoving = true;
                }
            }
            m_core.handlers.erase(it);
            return true;
        }
        return false;
    }

private:

    inline TMyEventHandlerIt findEventHandler(const TMyEventHandlerPtr& eventHandler) const noexcept
    {
        return std::find_if(m_core.handlers.cbegin(), m_core.handlers.cend(), [&eventHandler](const TMyEventHandlerPtr& oneHandler)
            {
                return (*oneHandler == *eventHandler);
            });
    }

    EventCore<TParams...> m_core;
    std::list<TMyHandlerRunner*> m_handlerRunners;
};

TEvent<app::Proto_SceneEntityAppearNotify*> EntityAppearEvent{};

namespace events::handlers
{
    template<class TMethodHolder, class ...TParams>
    struct IsMethodParamsCompatible
    {
    private:

        template<class TCheckedMethodHolder, class ...TCheckedParams>
        static constexpr std::true_type exists(decltype((std::declval<TCheckedMethodHolder>().m_innerHolder.get().*std::declval<TCheckedMethodHolder>().m_method)(std::declval<TCheckedParams>()...))* = nullptr) noexcept;

        template<class TCheckedMethodHolder, class ...TCheckedParams>
        static constexpr std::false_type exists(...) noexcept;

    public:

        static constexpr bool value = decltype(exists<TMethodHolder, TParams...>(nullptr))::value;
    };


    template<class TMethodHolder, class ...TParams>
    class MethodEventHandler : public AbstractEventHandler<TParams...>
    {
        using MyType = MethodEventHandler<TMethodHolder, TParams...>;
        using TMethodHolderPtr = std::shared_ptr<TMethodHolder>;

    public:

        MethodEventHandler(TMethodHolderPtr methodHolder) :
            AbstractEventHandler<TParams...>(),
            m_methodHolder(methodHolder)
        {
            assert(m_methodHolder != nullptr);
        }

        virtual void call(TParams... params) override
        {
            static_assert(IsMethodParamsCompatible<TMethodHolder, TParams...>::value, "Event and method arguments are not compatible");

            (m_methodHolder->m_innerHolder.get().*m_methodHolder->m_method)(params...);
        }

    protected:

        virtual bool isEquals(const AbstractEventHandler<TParams...>& other) const noexcept override
        {
            const MyType* _other = dynamic_cast<const MyType*>(&other);
            return (_other != nullptr && *m_methodHolder == *_other->m_methodHolder);
        }

    private:

        TMethodHolderPtr m_methodHolder;
    };


    template<class TObject, class TResult, class ...TParams>
    class MethodHolder
    {
        using MyType = MethodHolder<TObject, TResult, TParams...>;
        using TMethod = TResult(TObject::*)(TParams...);

    public:

        ~MethodHolder()
        {
            delete& m_innerHolder;
        }

        template<class ...TCallParams>
        operator TEventHandlerPtr<TCallParams...>()
        {
            return TEventHandlerPtr<TCallParams...>(new MethodEventHandler<MyType, TCallParams...>(m_me.lock()));
        }

        bool operator==(const MyType& other) const noexcept
        {
            return (&m_innerHolder.get() == &other.m_innerHolder.get() && m_method == other.m_method);
        }
        bool operator!=(const MyType& other) const noexcept
        {
            return !(*this == other);
        }

        // TObject typename is reserved by the enclosing template so need something different
        template<class TArgObject>
        static std::shared_ptr<MyType> create(TArgObject&& object, TMethod method)
        {
            std::shared_ptr<MyType> result(new MyType(std::forward<TArgObject>(object), method));
            result->m_me = result;
            return result;
        }

    private:

        template<class TArgObject>
        MethodHolder(TArgObject&& object, TMethod method) :
            m_innerHolder(createInnerHolder<TObject>(std::forward<TArgObject>(object))),
            m_method(method)
        {
            assert(m_method != nullptr);
        }

        AbstractInnerHolder<TObject>& m_innerHolder;
        TMethod m_method;

        std::weak_ptr<MyType> m_me;

        template<class TMethodHolder, class ...> friend class MethodEventHandler;
        template<class TMethodHolder, class ...> friend struct IsMethodParamsCompatible;
    };


    template<class TObject, class TResult, class ...TParams>
    std::shared_ptr<MethodHolder<std::decay_t<TObject>, TResult, TParams...>> createMethodEventHandler(TObject&& object, TResult(std::decay<TObject>::type::* method)(TParams...))
    {
        return MethodHolder<std::decay_t<TObject>, TResult, TParams...>::create(std::forward<TObject>(object), method);
    }
}

#define     METHOD_HANDLER( Object, Method )     createMethodEventHandler( Object, &Method )
#define     MY_METHOD_HANDLER( Method )          METHOD_HANDLER( *this, Method )

namespace config {
    template<class T>
    class Field : public internal::FieldBase<T>
    {
    public:
        using base = internal::FieldBase<T>;
        using base::operator=;
        using base::base;
    };

    namespace internal
    {
        template<typename T>
        std::vector<T> s_Fields;

        class FieldEntry {
        public:
            std::string m_Name;
            std::string m_Section;
            bool m_MultiProfile;
            nlohmann::json* m_Container;

            FieldEntry(const std::string& name, const std::string& sectionName, bool multiProfile = false)
                : m_Name(name), m_Section(sectionName), m_MultiProfile(multiProfile), m_Container(nullptr) {}
        };

        void AddField(std::shared_ptr<FieldEntry> field);

        inline std::string FixFieldName(const std::string& fieldName)
        {
            if (fieldName.substr(1, 1) == "_")
                return fieldName.substr(2);
            return fieldName;
        }
    }

    template<typename T, typename... Args>
    config::Field<T> CreateField(const std::string& name, const std::string& section, bool multiProfile, Args... args)
    {
        auto newField = Field<T>(name, section, T(args...), multiProfile);
        internal::s_Fields<Field<T>>.push_back(newField);
        internal::AddField(newField.entry());
        return newField;
    }

    template<typename T>
    std::vector<config::Field<T>>& GetFields()
    {
        return internal::s_Fields<Field<T>>;
    }
}

enum class Avatars
{
    Ayaka,
    Jean,
    Lisa,
    Barbara,
    Kaeya,
    Diluc,
    Razor,
    Ambor,
    Venti,
    Xiangling,
    Beidou,
    Xingqiu,
    Xiao,
    Ningguang,
    Klee,
    Zhongli,
    Fischl,
    Bennett,
    Tartaglia,
    Noel,
    Qiqi,
    Chongyun,
    Ganyu,
    Albedo,
    Diona,
    Mona,
    Keqing,
    Sucrose,
    Xinyan,
    Rosaria,
    Hutao,
    Kazuha,
    Feiyan,
    Yoimiya,
    Tohma,
    Eula,
    Shougun,
    Sayu,
    Kokomi,
    Gorou,
    Sara,
    Itto,
    Yae,
    Heizo,
    Yelan,
    Aloy,
    Shenhe,
    Yunjin,
    Shinobu,
    Ayato,
    Collei,
    Dori,
    Tighnari,
    Nilou,
    Cyno,
    Candace,
    Nahida,
    Layla,
    Wanderer,
    Faruzan,
    Yaoyao,
    Alhaitham,
    Dehya,
    Mika,
    Kaveh,
    Baizhu
};

const std::map<uint32_t, std::pair<Avatars, std::vector<uint32_t>>> m_AllTalents
{
    { 10000002, { Avatars::Ayaka, { 21, 22, 23, 24, 25, 26 } } },
    { 10000003, { Avatars::Jean, { 31, 32, 33, 34, 35, 36 } } },
    { 10000006, { Avatars::Lisa, { 41, 42, 43, 44, 45, 46 } } },
    { 10000014, { Avatars::Barbara, { 141, 142, 143, 144, 145, 146 } } },
    { 10000015, { Avatars::Kaeya, { 151, 152, 153, 154, 155, 156 } } },
    { 10000016, { Avatars::Diluc, { 161, 162, 163, 164, 165, 166 } } },
    { 10000020, { Avatars::Razor, { 201, 202, 203, 204, 205, 206 } } },
    { 10000021, { Avatars::Ambor, { 211, 212, 213, 214, 215, 216 } } },
    { 10000022, { Avatars::Venti, { 221, 222, 223, 224, 225, 226 } } },
    { 10000023, { Avatars::Xiangling, { 231, 232, 233, 234, 235, 236 } } },
    { 10000024, { Avatars::Beidou, { 241, 242, 243, 244, 245, 246 } } },
    { 10000025, { Avatars::Xingqiu, { 251, 252, 253, 254, 255, 256 } } },
    { 10000026, { Avatars::Xiao, { 261, 262, 263, 264, 265, 266 } } },
    { 10000027, { Avatars::Ningguang, { 271, 272, 273, 274, 275, 276 } } },
    { 10000029, { Avatars::Klee, { 291, 292, 293, 294, 295, 296 } } },
    { 10000030, { Avatars::Zhongli, { 301, 302, 303, 304, 305, 306 } } },
    { 10000031, { Avatars::Fischl, { 311, 312, 313, 314, 315, 316 } } },
    { 10000032, { Avatars::Bennett, { 321, 322, 323, 324, 325, 326 } } },
    { 10000033, { Avatars::Tartaglia, { 331, 332, 333, 334, 335, 336 } } },
    { 10000034, { Avatars::Noel, { 341, 342, 343, 344, 345, 346 } } },
    { 10000035, { Avatars::Qiqi, { 351, 352, 353, 354, 355, 356 } } },
    { 10000036, { Avatars::Chongyun, { 361, 362, 363, 364, 365, 366 } } },
    { 10000037, { Avatars::Ganyu, { 371, 372, 373, 374, 375, 376 } } },
    { 10000038, { Avatars::Albedo, { 381, 382, 383, 384, 385, 386 } } },
    { 10000039, { Avatars::Diona, { 391, 392, 393, 394, 395, 396 } } },
    { 10000041, { Avatars::Mona, { 411, 412, 413, 414, 415, 416 } } },
    { 10000042, { Avatars::Keqing, { 421, 422, 423, 424, 425, 426 } } },
    { 10000043, { Avatars::Sucrose, { 431, 432, 433, 434, 435, 436 } } },
    { 10000044, { Avatars::Xinyan, { 441, 442, 443, 444, 445, 446 } } },
    { 10000045, { Avatars::Rosaria, { 451, 452, 453, 454, 455, 456 } } },
    { 10000046, { Avatars::Hutao, { 461, 462, 463, 464, 465, 466 } } },
    { 10000047, { Avatars::Kazuha, { 471, 472, 473, 474, 475, 476 } } },
    { 10000048, { Avatars::Feiyan, { 481, 482, 483, 484, 485, 486 } } },
    { 10000049, { Avatars::Yoimiya, { 491, 492, 493, 494, 495, 496 } } },
    { 10000050, { Avatars::Tohma, { 501, 502, 503, 504, 505, 506 } } },
    { 10000051, { Avatars::Eula, { 511, 512, 513, 514, 515, 516 } } },
    { 10000052, { Avatars::Shougun, { 521, 522, 523, 524, 525, 526 } } },
    { 10000053, { Avatars::Sayu, { 531, 532, 533, 534, 535, 536 } } },
    { 10000054, { Avatars::Kokomi, { 541, 542, 543, 544, 545, 546 } } },
    { 10000055, { Avatars::Gorou, { 551, 552, 553, 554, 555, 556 } } },
    { 10000056, { Avatars::Sara, { 561, 562, 563, 564, 565, 566 } } },
    { 10000057, { Avatars::Itto, { 571, 572, 573, 574, 575, 576 } } },
    { 10000058, { Avatars::Yae, { 581, 582, 583, 584, 585, 586 } } },
    { 10000059, { Avatars::Heizo, { 591, 592, 593, 594, 595, 596 } } },
    { 10000060, { Avatars::Yelan, { 601, 602, 603, 604, 605, 606 } } },
    { 10000062, { Avatars::Aloy, { 621, 622, 623, 624, 625, 626 } } },
    { 10000063, { Avatars::Shenhe, { 631, 632, 633, 634, 635, 636 } } },
    { 10000064, { Avatars::Yunjin, { 641, 642, 643, 644, 645, 646 } } },
    { 10000065, { Avatars::Shinobu, { 651, 652, 653, 654, 655, 656 } } },
    { 10000066, { Avatars::Ayato, { 661, 662, 663, 664, 665, 666 } } },
    { 10000067, { Avatars::Collei, { 671, 672, 673, 674, 675, 676 } } },
    { 10000068, { Avatars::Dori, { 681, 682, 683, 684, 685, 686 } } },
    { 10000069, { Avatars::Tighnari, { 691, 692, 693, 694, 695, 696 } } },
    { 10000070, { Avatars::Nilou, { 701, 702, 703, 704, 705, 706 } } },
    { 10000071, { Avatars::Cyno, { 711, 712, 713, 714, 715, 716 } } },
    { 10000072, { Avatars::Candace, { 721, 722, 723, 724, 725, 726 } } },
    { 10000073, { Avatars::Nahida, { 731, 732, 733, 734, 735, 736 } } },
    { 10000074, { Avatars::Layla, { 741, 742, 743, 744, 745, 746 } } },
    { 10000075, { Avatars::Wanderer, { 751, 752, 753, 754, 755, 756 } } },
    { 10000076, { Avatars::Faruzan, { 761, 762, 763, 764, 765, 766 } } },
    { 10000077, { Avatars::Yaoyao, { 771, 772, 773, 774, 775, 776 } } },
    { 10000078, { Avatars::Alhaitham, { 781, 782, 783, 784, 785, 786 } } },
    { 10000079, { Avatars::Dehya, { 791, 792, 793, 794, 795, 796 } } },
    { 10000080, { Avatars::Mika, { 801, 802, 803, 804, 805, 806 } } },
    { 10000081, { Avatars::Kaveh, { 811, 812, 813, 814, 815, 816 } } },
    { 10000082, { Avatars::Baizhu, { 821, 822, 823, 824, 825, 826 } } },
};

std::vector<std::pair<config::Field<bool>, Avatars>> m_Talents;

namespace il2fns {

}