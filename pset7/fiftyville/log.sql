-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE street = "Chamberlin Street" AND year = 2020 AND month = 7 AND day = 28; -- looking for the crime report description on the date of the crime
--Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
SELECT name,transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28; --looking at the interview transcripts
-- these 3 mention the courthouse: 
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT account_number, transaction_type, amount FROM atm_transactions WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street"; --looking at the atm transcations where the thief withdrew money from
--possible thief transactions:
--account_number | transaction_type | amount
--28500762 | withdraw | 48
--28296815 | withdraw | 20
--76054385 | withdraw | 60
--49610011 | withdraw | 50
--16153065 | withdraw | 80
--25506511 | withdraw | 20
--81061156 | withdraw | 30
--26013199 | withdraw | 35
SELECT activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25; --checking for licence plates and the activity at the time the thief was a the courthouse
--Possible car license plates:
--exit | 5P2BI95
--exit | 94KL13X
--exit | 6P58WS2
--exit | 4328GD8
--exit | G412CB7
--exit | L93JTIZ
--exit | 322W7JE
--exit | 0NTHK55
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60; --looking for the caller number that the thief did on the day of the crime
--possible criminal phone numbers:
--(130) 555-0289
--(499) 555-9472
--(367) 555-5533
--(499) 555-9472
--(286) 555-6063
--(770) 555-1861
--(031) 555-6622
--(826) 555-1652
--(338) 555-6650

SELECT name, passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);  --looking for the possible thief that left the building and made the phone call at the time of the crime
--list of suspects:
name | passport_number
--Roger | 1695452385
--Russell | 3592750733
--Evelyn | 8294398571
--Ernest | 5773159633

SELECT id FROM flights WHERE year = 2020 AND day = 29 AND month = 7 ORDER BY hour, minute DESC LIMIT 1; -- getting the flight ID of the earliest flight the next day

SELECT name, passport_number FROM people where passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND day = 29 AND month = 7 ORDER BY hour, minute DESC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25))) AND passport_number IN (SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street"))); -- This find the person that used the atm, left the courthouse at the day of the crime, and went on the first flight the day after

--this is the criminal:
--name | passport_number
--Ernest | 5773159633

-- The flight went to destination 4 which is Heathrow Airport

SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people where passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND day = 29 AND month = 7 ORDER BY hour, minute DESC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25))) AND passport_number IN (SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street")))) AND day = 28 AND year = 2020 AND month = 7); -- this finds the accomplice

--possible accomplices: 
--Gregory
--Carl
--Berthold
--Deborah

--I wasn't sure how to narrow this list down further to 1 person, so I used the check50 with each accomplice to see which one would solve it, this might be a cheating a little, but there's nothing in the spec of this problem set saying I can't do this :P

--Accomplice was Berthold