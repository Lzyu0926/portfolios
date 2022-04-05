/*過去14天到過的地方*/
with place_list as (
    select
        *
    from
        record
    where
        phone_number in (
            select
                phone_number
            from
                (
                    /*這個人全部的電話*/
                    select
                        *
                    from
                        person
                        inner join phone on person.identity_card_id = phone.identity_card_id
                        and person.identity_card_id = 'M157111646'
                ) as phone_numbers
        )
        and time > NOW() - INTERVAL '14 DAYS'
)
select
    person.name,
    person.identity_card_id,
    place.address,
    record.time
from
    record
    inner join place_list on place_list.place_id = record.place_id
    and record.time < place_list.time + INTERVAL '3 HOUR'
    and record.time > place_list.time - INTERVAL '3 HOUR'
    inner join phone on record.phone_number = phone.phone_number
    inner join person on phone.identity_card_id = person.identity_card_id
    inner join place on record.place_id = place.place_id
order by
    record.time