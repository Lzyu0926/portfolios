CREATE TABLE Person (
    identity_card_id VARCHAR(50),
    name VARCHAR(50),
    PRIMARY KEY (identity_card_id)
);

CREATE TABLE Phone (
    phone_number VARCHAR(50),
    identity_card_id VARCHAR(50),
    PRIMARY KEY (phone_number)
);

CREATE TABLE Place (
    place_id VARCHAR(50),
    name VARCHAR(50),
    address VARCHAR(100),
    phone_number VARCHAR(50),
    PRIMARY KEY (place_id)
);

CREATE TABLE Record (
    phone_number VARCHAR(50),
    place_id VARCHAR(50),
    time TIMESTAMP
);