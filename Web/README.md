# Struktur Database
| Tabel| Struktur                                       | 
|-----------|---------------------------------------------------|
| device        | id, name, info                          |
| setting | id, device_id, type, interval_on, interval_off, timestamp |
| data | id, device_id, data, timestamp|
---
Relation device_id is id in table device.
