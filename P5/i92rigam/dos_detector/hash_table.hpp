#ifndef __HASH_TABLE__
#define __HASH_TABLE__
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <vector>
#include <list>
#include <utility>
#include <memory>


/**
 * @brief Implement the HashTable[K,V] ADT.
 * The template parameter keyToInt is a functional to transform
 * values of type K into size_t. It must be implement the interface:
 *    size_t operator()(K const&k)
 */
template<class K, class V, class keyToInt>
class HashTable
{
public:
    /** @name Life cicle.*/
    /** @{*/

    /**
      * @brief Create a new HashTable.
      * @post is_empty()
      * @post not is_valid()
      */
    HashTable(size_t m, uint64_t a=32, uint64_t b=3, uint64_t p=4294967311l,
              keyToInt key_to_int=keyToInt())
    {
        a_ = a;
        b_ = b;
        p_ = p;
        m_ = m;

        hash_table_.resize(m);
        num_of_valid_keys_ = 0;
        current_it_ = hash_table_[0].begin();
        indice_current_ = 0;
        key_to_int_ = key_to_int;

        assert(is_empty());
        assert(!is_valid());
    }
    /** @}*/

    /** @name Observers*/
    /** @{*/

    /**
     * @brief Is the table empty?
     * @return true if it is empty.
     */
    bool is_empty()
    {
        bool is_empty;
        (num_of_valid_keys_ == 0) ? (is_empty = true) : (is_empty = false);
        return  is_empty;
    }

    /**
     * @brief is the cursor at a valid position?
     * @return true if the cursor is at a valid position.
     */
    bool is_valid() const
    {
        bool is_valid = false;

        if(indice_current_ != hash_table_.size())
        {
            for(auto i = hash_table_[indice_current_].begin(); i != hash_table_[indice_current_].end() && is_valid == false; i++)
            {
                if(i == current_it_)
                {
                    is_valid = true;
                }
            }
        }

        return is_valid;
    }

    /**
     * @brief Get the number of valid keys in the table.
     * @return the number of valid keys in the table.
     */
    size_t num_of_valid_keys() const
    {
        return num_of_valid_keys_;
    }

    /**
     * @brief Compute the load factor of the table.
     * @return the load factor of the table.
     */
    float load_factor() const
    {
        return num_of_valid_keys_ / m_;
    }

    /**
     * @brief Has the table this key?
     * @param k the key to find.
     * @return true if the key is saved into the table.
     * @warning The cursor is not affected by this operation.
     */
    bool has(K const& k) const
    {
        bool has = false;
        auto key = hash(key_to_int_(k));

        for (auto i = hash_table_[key].begin(); i != hash_table_[key].end() && has == false; i++)
        {
            if(i->first == k)
            {
                has = true;
            }
        }
        return has;
    }


    /**
     * @brief Get the key at cursor.
     * @return return the key of the cursor.
     */
    K const& get_key() const
    {
        assert(is_valid());
        return current_it_->first;
    }

    /**
     * @brief Get tha value at cursor.
     * @return return the value of the cursor.
     */
    V const& get_value() const
    {
        assert(is_valid());
        return current_it_->second;
    }

    /**
     * @brief hash a key value k.
     * @return h = ((int(k)*a + b) % p) % m
     */
    size_t
    hash(uint64_t k) const
    {
        return ((((k * a_) + b_) % p_) % m_);
    }

    /** @}*/

    /** @name Modifiers*/
    /** @{*/

    /**
     * @brief Find a key value.
     * @return true if the key is found.
     * @post !is_valid() or get_key()==k
     */
    bool find(K const& k)
    {
        bool is_found=false;

        if(!is_empty())
        {
            auto key = hash(key_to_int_(k));
            for (auto i = hash_table_[key].begin(); i != hash_table_[key].end() && is_found != true; i++)
            {
                if(i->first == k)
                {
                    indice_current_ = key;
                    current_it_ = i;
                    is_found = true;
                }
            }
        }

        return is_found;
    }

    /**
     * @brief insert a new entry.
     * If the key is currently in the table, the value is updated.
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v;
     * @post not old(has(k)) -> num_of_valid_keys() = old(num_of_valid_keys())+1
     */
    void insert(K const& k, V const& v)
    {
#ifndef NDEBUG //In Relase mode this macro is defined.
        bool old_has = has(k);
        size_t old_num_of_valid_keys = num_of_valid_keys();
#endif

        if(find(k) == true)
        {
            set_value(v);
        }
        else
        {
            indice_current_ = hash(key_to_int_(k));
            hash_table_[indice_current_].push_front(std::make_pair(k,v));
            num_of_valid_keys_++;
            current_it_ = hash_table_[indice_current_].begin();
            if(load_factor() > 0.9)
            {
                rehash();
            }
        }

        assert(is_valid());
        assert(get_key()==k);
        assert(get_value()==v);
        assert(old_has || (num_of_valid_keys()==old_num_of_valid_keys+1));
    }

    /**
     * @brief remove the entry at the cursor position.
     * The cursor will be move to the next valid position if there is.
     * @pre is_valid()
     * @post !is_valid() || old(goto_next() && get_key())==get_key()
     * @post num_of_valid_keys() = old(num_of_valid_keys())-1
     */
    void remove()
    {
        assert(is_valid());
#ifndef NDEBUG //In Relase mode this macro is defined.
        size_t old_n_valid_keys = num_of_valid_keys();
#endif

        auto indice_current_aux = indice_current_;
        auto current_it_aux = current_it_;

        goto_next(); //move the cursor to next position.

        hash_table_[indice_current_aux].erase(current_it_aux);
        num_of_valid_keys_--;

        assert( (num_of_valid_keys()+1)==old_n_valid_keys );
        return;
    }

    /**
     * @brief set the value of the entry at the cursor position.
     */
    void set_value(const V& v)
    {
        assert(is_valid());
        current_it_->second = v;
    }

    /**
     * @brief rehash the table to double size.
     * @warning A new hash function is random selected.
     * @post old.is_valid() implies is_valid() && old.get_key()==get_key() && old.get_value()==get_value()
     */
    void rehash()
    {
#ifndef NDEBUG  //In Relase mode this macro is defined.
        bool old_is_valid = is_valid();
        K old_key;
        V old_value;
        if (old_is_valid)
        {
            old_key = get_key();
            old_value = get_value();
        }
#endif

        auto auxiliar_key = current_it_->first;

        uint64_t P = p_;
        const uint64_t a = 1 + static_cast<uint64_t>(std::rand()/(RAND_MAX+1.0) * static_cast<double>(P-1));
        const uint64_t b = static_cast<uint64_t>(std::rand()/(RAND_MAX+1.0) * static_cast<double>(P));

        size_t M = m_;
        HashTable<K, V, keyToInt> new_table (M*2, a, b);

        goto_begin();
        while (is_valid())
        {
            new_table.insert(get_key(),get_value());
            goto_next();
        }

        (*this) = new_table;

        find(auxiliar_key);

        //post condition
        assert(!old_is_valid || (is_valid() && old_key==get_key() && old_value==get_value()));
    }

    /**
     * @brief move the cursor to the first valid entry.
     * @post is_empty() || is_valid()
     */
    void goto_begin()
    {

        for (size_t i = 0; i < hash_table_.size(); i++)
        {
            if(!hash_table_[i].empty())
            {
                current_it_ = hash_table_[i].begin();
                indice_current_ = i;
                break;
            }
        }

        assert(is_empty() || is_valid());
    }

    /**
     * @brief Move the cursor to next valid position.
     * @post not is_valid() marks none any more valid entry exists.
     */
    void goto_next()
    {
        assert(is_valid());

        current_it_++;

        if(current_it_ == hash_table_[indice_current_].end())
        {
            size_t i = indice_current_ + 1;
            while(i < hash_table_.size() && hash_table_[i].empty())
            {
                i++;
            }
            if(i < hash_table_.size() && !hash_table_[i].empty())
            {
                current_it_ = hash_table_[i].begin();
                indice_current_ = i;
                assert(is_valid());
            }
            else
            {
                indice_current_ = hash_table_.size();
            }
        }

    }
    /** @} */

protected:

    std::vector<std::list<std::pair<K, V>>> hash_table_;
    size_t m_;
    keyToInt key_to_int_;
    uint64_t a_;
    uint64_t b_;
    uint64_t p_;
    size_t indice_current_;
    typename std::list<std::pair<K, V>>::iterator current_it_;
    size_t num_of_valid_keys_;
};

#endif
