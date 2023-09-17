--All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First try to find date and time with street;
SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- crime_scene id = 295, 297 with description Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted
-- today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.


SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;



                                                                                                               |
-- | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
-- +---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+



SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;




-- Bakery logs
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- person with license plate 13FNH73 entered bakery 10:14



-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+


SELECT * FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE people.id IN (SELECT people.id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25));

-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | account_number | person_id | creation_year |   id   | name  |  phone_number  | passport_number | license_plate |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | 49610011       | 686048    | 2010          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 26013199       | 514354    | 2012          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 25506511       | 396669    | 2014          | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 28500762       | 467400    | 2014          | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 56171033       | 243696    | 2018          | 243696 | Barry | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+

SELECT * FROM atm_transactions
WHERE account_number IN (SELECT account_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE people.id IN (SELECT people.id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)))
AND year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street';

-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+

SELECT * FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE account_number IN (SELECT account_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE people.id IN (SELECT people.id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)))
AND year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street');

-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | account_number | person_id | creation_year |   id   | name  |  phone_number  | passport_number | license_plate |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | 49610011       | 686048    | 2010          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 26013199       | 514354    | 2012          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 25506511       | 396669    | 2014          | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 28500762       | 467400    | 2014          | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+


SELECT * FROM phone_calls
WHERE year = 2021 AND day = 28 AND month = 7 AND caller IN (SELECT phone_number FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE account_number IN (SELECT account_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE people.id IN (SELECT people.id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)))
AND year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street'));

-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      |
-- | 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       |
-- +-----+----------------+----------------+------+-------+-----+----------+


SELECT * FROM passengers
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city = 'Fiftyville' AND flights.year = 2021 AND flights.month = 7 AND
passengers.passport_number IN (SELECT passport_number FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE account_number IN (SELECT account_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE people.id IN (SELECT people.id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)))
AND year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street'));





-- ------------+-----------------------------+------------+
-- | flight_id | passport_number | seat | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |          full_name          |    city    |
-- +-----------+-----------------+------+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+
-- | 11        | 8496433585      | 5D   | 11 | 8                 | 12                     | 2021 | 7     | 30  | 13   | 7      | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- | 18        | 3592750733      | 4C   | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- | 36        | 5773159633      | 4A   | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- | 36        | 8496433585      | 7B   | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- | 54        | 3592750733      | 6C   | 54 | 8                 | 5                      | 2021 | 7     | 30  | 10   | 19     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- +-----------+-----------------+------+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+


SELECT city FROM airports
WHERE airports.id = 6;